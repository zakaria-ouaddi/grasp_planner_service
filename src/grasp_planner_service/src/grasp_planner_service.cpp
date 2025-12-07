#include "grasp_planner_service/grasp_planner_service.hpp"
#include <Eigen/Geometry>
#include <VirtualRobot/CollisionDetection/CDManager.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/IK/DifferentialIK.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <algorithm> // For std::sort

namespace grasp_planner_service {

// This constructor is now correct. It no longer initializes
// the Simox variables that we removed from the header.
GraspPlannerService::GraspPlannerService() : Node("grasp_planner_service") {
  service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
      "plan_grasp", std::bind(&GraspPlannerService::handle_service, this,
                              std::placeholders::_1, std::placeholders::_2));

  RCLCPP_INFO(this->get_logger(),
              "Grasp Planner Service (Phase 1-3) initialized");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) {
  RCLCPP_INFO(this->get_logger(), "Received grasp request for object: %s",
              request->object_model_path.c_str());

  // --- THREAD-SAFETY: All Simox objects are declared LOCALLY ---
  VirtualRobot::RobotPtr robot = nullptr;
  VirtualRobot::GraspableSensorizedObjectPtr object = nullptr;
  VirtualRobot::EndEffectorPtr eef = nullptr;
  VirtualRobot::GraspSetPtr grasps = nullptr;
  GraspStudio::GraspQualityMeasureWrenchSpacePtr qualityMeasure = nullptr;
  GraspStudio::ApproachMovementSurfaceNormalPtr approach = nullptr;
  GraspStudio::GenericGraspPlannerPtr planner = nullptr;

  try {
    // 1. Load the robot model
    robot = VirtualRobot::RobotIO::loadRobot(request->robot_model_path);
    if (!robot) {
      response->success = false;
      response->error_message =
          "Failed to load robot model: " + request->robot_model_path;
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // 2. Get end effector
    eef = robot->getEndEffector(request->end_effector_name);
    if (!eef) {
      response->success = false;
      response->error_message =
          "End effector '" + request->end_effector_name + "' not found";
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // 3. Set preshape if specified
    if (!request->preshape_name.empty()) {
      if (eef->hasPreshape(request->preshape_name)) {
        eef->setPreshape(request->preshape_name);
      } else {
        response->success = false;
        response->error_message =
            "Preshape '" + request->preshape_name + "' not found";
        RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
        return;
      }
    }

    // 4. Load object model
    object = VirtualRobot::ObjectIO::loadManipulationObject(
        request->object_model_path);
    if (!object) {
      response->success = false;
      response->error_message =
          "Failed to load object model: " + request->object_model_path;
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // 5. SET OBJECT POSE (Phase 1.1 Requirement)
    Eigen::Matrix4f eigen_object_pose =
        conversions::rosPoseToEigen(request->object_pose);
    object->setGlobalPose(eigen_object_pose);

    // 6. Initialize grasp planning components
    qualityMeasure.reset(
        new GraspStudio::GraspQualityMeasureWrenchSpace(object));
    qualityMeasure->calculateObjectProperties();

    approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(
        object, eef, request->preshape_name));

    // Create new grasp set
    grasps.reset(new VirtualRobot::GraspSet("ros_planned_grasps",
                                            robot->getType(), eef->getName()));

    // Setup planner with quality threshold and force closure requirement (last
    // param = true)
    planner.reset(new GraspStudio::GenericGraspPlanner(
        grasps, qualityMeasure, approach, request->quality_threshold, true));
    planner->setVerbose(false); // Set to true for detailed Simox logging

    // 7. PLAN GRASPS (Phase 1.1 Requirement)
    int grasps_planned =
        planner->plan(request->num_grasps_to_plan, request->timeout_ms);

    if (grasps_planned <= 0 || grasps->getSize() == 0) {
      response->success = false;
      response->error_message = "No valid grasps found";
      RCLCPP_WARN(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    RCLCPP_INFO(this->get_logger(),
                "Found %d grasps. Converting to ROS format.", grasps_planned);

    // --- PHASE 2: REACHABILITY & COLLISION AVOIDANCE ---

    // 2.1 Setup IK Solver (if chain specified)
    VirtualRobot::DifferentialIKPtr ikSolver = nullptr;
    VirtualRobot::RobotNodeSetPtr rns = nullptr;
    if (!request->kinematic_chain_name.empty()) {
      rns = robot->getRobotNodeSet(request->kinematic_chain_name);
      if (rns) {
        ikSolver.reset(new VirtualRobot::DifferentialIK(rns));
      } else {
        RCLCPP_WARN(this->get_logger(),
                    "Kinematic chain '%s' not found. Skipping IK check.",
                    request->kinematic_chain_name.c_str());
      }
    }

    // 2.2 Setup Collision Detection
    VirtualRobot::CDManagerPtr cdManager(new VirtualRobot::CDManager());
    VirtualRobot::SceneObjectSetPtr rnsColModel;
    if (rns) {
      rnsColModel.reset(new VirtualRobot::SceneObjectSet("RobotNodes"));
      for (auto node : rns->getAllRobotNodes()) {
        rnsColModel->addSceneObject(node);
      }
      cdManager->addCollisionModel(rnsColModel);
    }

    // Use the struct defined in the header
    std::vector<ValidGrasp> valid_grasps;

    RCLCPP_INFO(this->get_logger(), "Processing %d candidate grasps...",
                (int)grasps->getSize());

    for (size_t i = 0; i < grasps->getSize(); ++i) {
      VirtualRobot::GraspPtr grasp = grasps->getGrasp(i);
      Eigen::Matrix4f global_tcp_pose =
          grasp->getTcpPoseGlobal(object->getGlobalPose());

      // --- REACHABILITY CHECK ---
      if (ikSolver) {
        ikSolver->setGoal(global_tcp_pose);
        bool reachable = ikSolver->solveIK();

        if (!reachable) {
          continue;
        }
      }

      // --- COLLISION CHECK ---
      if (rnsColModel && cdManager->isInCollision(rnsColModel)) {
        // Collision detected in this configuration
        continue;
      }

      // If we get here, the grasp is valid
      ValidGrasp vg;
      vg.grasp = grasp;
      vg.quality = grasp->getQuality();
      vg.pose = conversions::eigenToRosPose(global_tcp_pose);
      valid_grasps.push_back(vg);
    }

    // --- RANKING ---
    // Sort by quality (descending)
    std::sort(valid_grasps.begin(), valid_grasps.end(),
              [](const ValidGrasp &a, const ValidGrasp &b) {
                return a.quality > b.quality;
              });

    RCLCPP_INFO(this->get_logger(),
                "Found %zu reachable and collision-free grasps.",
                valid_grasps.size());

    if (valid_grasps.empty()) {
      response->success = false;
      response->error_message = "No reachable/collision-free grasps found.";
      return;
    }

    // Fill Response
    for (const auto &vg : valid_grasps) {
      response->grasp_poses.push_back(vg.pose);
      response->qualities.push_back(vg.quality);
      response->are_force_closure.push_back(true);
    }

    response->success = true;
    response->error_message = "Successfully planned " +
                              std::to_string(valid_grasps.size()) + " grasps.";
    RCLCPP_INFO(this->get_logger(), "%s", response->error_message.c_str());

  }
  // 9. ERROR HANDLING (Phase 1.3 Requirement)
  catch (const VirtualRobot::VirtualRobotException &e) {
    response->success = false;
    response->error_message = std::string("Simox API Error: ") + e.what();
    RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
  } catch (const std::exception &e) {
    response->success = false;
    response->error_message = std::string("Standard Exception: ") + e.what();
    RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
  }
}

} // namespace grasp_planner_service
