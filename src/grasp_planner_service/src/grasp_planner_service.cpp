#include "grasp_planner_service/grasp_planner_service.hpp"
#include <Eigen/Geometry>
#include <VirtualRobot/CollisionDetection/CDManager.h>
#include <VirtualRobot/CollisionDetection/CollisionModel.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/IK/DifferentialIK.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <algorithm> // For std::sort
#include <filesystem>
#include <fstream>
#include <iostream>

namespace grasp_planner_service {

// This constructor is now correct. It no longer initializes
// the Simox variables that we removed from the header.
GraspPlannerService::GraspPlannerService() : Node("grasp_planner_service") {
  service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
      "plan_grasp", std::bind(&GraspPlannerService::handle_service, this,
                              std::placeholders::_1, std::placeholders::_2));

  // Initialize publisher for markers (Standard QoS to match default RViz)
  markers_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
      "grasp_markers", rclcpp::QoS(10));

  // Initialize TF broadcaster
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

  RCLCPP_INFO(this->get_logger(),
              "Grasp Planner Service (Phase 1-3) initialized");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) {
  RCLCPP_INFO(this->get_logger(), "Received grasp request for object: %s",
              request->object_model_path.c_str());

  // --- THREAD-SAFETY: Reset member variables for this request ---
  // Note: Is it thread safe? "this->robot" implies shared state.
  // If we want thread safety we should not use members, but for this Bridge I
  // will use members assuming single-threaded service callback execution or
  // accepted risk for now.
  this->robot = nullptr;
  this->object = nullptr;

  VirtualRobot::EndEffectorPtr eef = nullptr;
  VirtualRobot::GraspSetPtr grasps = nullptr;
  GraspStudio::GraspQualityMeasureWrenchSpacePtr qualityMeasure = nullptr;
  GraspStudio::ApproachMovementSurfaceNormalPtr approach = nullptr;
  GraspStudio::GenericGraspPlannerPtr planner = nullptr;

  try {
    // 1. Load the robot model
    this->robot = VirtualRobot::RobotIO::loadRobot(request->robot_model_path);
    if (!this->robot) {
      response->success = false;
      response->error_message =
          "Failed to load robot model: " + request->robot_model_path;
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // DEBUG: Robot loading verification
    RCLCPP_INFO(this->get_logger(), "Robot loaded: %s, DOFs: %zu",
                this->robot->getType().c_str(),
                this->robot->getRobotNodes().size());

    // NEW: Publish Robot Visuals immediately
    publish_robot_visuals(this->robot);

    // 2. Get end effector
    eef = this->robot->getEndEffector(request->end_effector_name);
    if (!eef) {
      response->success = false;
      response->error_message =
          "End effector '" + request->end_effector_name + "' not found";
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // DEBUG: End effector verification
    RCLCPP_INFO(this->get_logger(), "End effector found: %s",
                eef->getName().c_str());
    if (eef->getTcp()) {
      Eigen::Matrix4f tcp_pose = eef->getTcp()->getGlobalPose();
      RCLCPP_INFO(this->get_logger(),
                  "TCP position (mm): x=%.1f, y=%.1f, z=%.1f", tcp_pose(0, 3),
                  tcp_pose(1, 3), tcp_pose(2, 3));
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
    this->object = VirtualRobot::ObjectIO::loadManipulationObject(
        request->object_model_path);
    if (!this->object) {
      response->success = false;
      response->error_message =
          "Failed to load object model: " + request->object_model_path;
      RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    // DEBUG: Object loading verification
    RCLCPP_INFO(this->get_logger(), "Object loaded: %s",
                this->object->getName().c_str());

    // CRITICAL: Check object bounding box to detect scale issues
    // Compute manually from visualization mesh
    if (this->object->getVisualization() &&
        this->object->getVisualization()->getTriMeshModel()) {
      auto mesh = this->object->getVisualization()->getTriMeshModel();
      if (mesh->vertices.size() > 0) {
        Eigen::Vector3f min_pt = mesh->vertices[0];
        Eigen::Vector3f max_pt = mesh->vertices[0];
        for (const auto &v : mesh->vertices) {
          min_pt = min_pt.cwiseMin(v);
          max_pt = max_pt.cwiseMax(v);
        }
        float size_x = max_pt(0) - min_pt(0);
        float size_y = max_pt(1) - min_pt(1);
        float size_z = max_pt(2) - min_pt(2);
        RCLCPP_INFO(this->get_logger(), "Object bounding box (mm):");
        RCLCPP_INFO(this->get_logger(), "  Min: (%.1f, %.1f, %.1f)", min_pt(0),
                    min_pt(1), min_pt(2));
        RCLCPP_INFO(this->get_logger(), "  Max: (%.1f, %.1f, %.1f)", max_pt(0),
                    max_pt(1), max_pt(2));
        RCLCPP_INFO(this->get_logger(), "  Size: (%.1f, %.1f, %.1f)", size_x,
                    size_y, size_z);
      }
    } else {
      RCLCPP_WARN(this->get_logger(),
                  "Object has no visualization mesh - cannot check size");
    }

    // 5. DEFER OBJECT POSE - Keep object at origin for grasp planning
    // (Simox ApproachMovementSurfaceNormal requires object at origin)
    Eigen::Matrix4f eigen_object_pose =
        conversions::rosPoseToEigen(request->object_pose);
    // COMMENTED OUT: this->object->setGlobalPose(eigen_object_pose);
    // Will set pose AFTER grasp planning for visualization

    // DEBUG: Log requested object pose (not yet applied)
    RCLCPP_INFO(this->get_logger(),
                "Requested object pose (mm): x=%.1f, y=%.1f, z=%.1f",
                eigen_object_pose(0, 3), eigen_object_pose(1, 3),
                eigen_object_pose(2, 3));

    // --- BROADCAST TRANSFORM (Phase 3 Fix) ---
    geometry_msgs::msg::TransformStamped t;
    t.header.stamp = this->now();
    t.header.frame_id = "world";
    t.child_frame_id = "object_frame";
    t.transform.translation.x = request->object_pose.position.x;
    t.transform.translation.y = request->object_pose.position.y;
    t.transform.translation.z = request->object_pose.position.z;
    t.transform.rotation = request->object_pose.orientation;
    tf_broadcaster_->sendTransform(t);

    // --- VISUALIZATION: Always publish object marker ---
    publish_object_marker(eigen_object_pose);

    // 6. Initialize grasp planning components (CORRECT ORDER FROM PHASE 1)
    qualityMeasure.reset(
        new GraspStudio::GraspQualityMeasureWrenchSpace(this->object));

    // Create approach FIRST (before calculating properties)
    approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(
        this->object, eef, request->preshape_name));

    // CRITICAL: Clone the EEF (Phase 1 requirement)
    VirtualRobot::RobotPtr eefCloned = approach->getEEFRobotClone();

    // THEN calculate object properties
    qualityMeasure->calculateObjectProperties();

    // Create new grasp set
    grasps.reset(new VirtualRobot::GraspSet(
        "ros_planned_grasps", this->robot->getType(), eef->getName()));

    // Setup planner with quality threshold and force closure requirement (last
    // param = true)
    // Setup planner (Force Closure optional for better hit rate)
    planner.reset(new GraspStudio::GenericGraspPlanner(
        grasps, qualityMeasure, approach, request->quality_threshold, false));
    planner->setVerbose(true); // Keep verbose for now

    // 7. PLAN GRASPS (Phase 1.1 Requirement)
    int grasps_planned =
        planner->plan(request->num_grasps_to_plan, request->timeout_ms);

    if (grasps_planned <= 0 || grasps->getSize() == 0) {
      response->success = false;
      response->error_message = "No valid grasps found";
      RCLCPP_WARN(this->get_logger(), "%s", response->error_message.c_str());
      return;
    }

    RCLCPP_INFO(this->get_logger(), "Generated %d candidate grasps at origin",
                (int)grasps->getSize());

    // NOW move object to requested pose for Phase 2 (reachability/collision
    // checking)
    this->object->setGlobalPose(eigen_object_pose);
    RCLCPP_INFO(this->get_logger(),
                "Moved object to pose (mm): x=%.1f, y=%.1f, z=%.1f",
                eigen_object_pose(0, 3), eigen_object_pose(1, 3),
                eigen_object_pose(2, 3));

    // Re-publish object marker at correct pose
    publish_object_marker(eigen_object_pose);

    RCLCPP_INFO(this->get_logger(),
                "Found %d grasps. Converting to ROS format.", grasps_planned);

    // --- PHASE 2: REACHABILITY & COLLISION AVOIDANCE ---

    // 2.1 Setup IK Solver (if chain specified)
    VirtualRobot::DifferentialIKPtr ikSolver = nullptr;
    VirtualRobot::RobotNodeSetPtr rns = nullptr;
    if (!request->kinematic_chain_name.empty()) {
      rns = this->robot->getRobotNodeSet(request->kinematic_chain_name);
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
          grasp->getTcpPoseGlobal(this->object->getGlobalPose());

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

    // --- PHASE 3: VISUALIZATION ---
    publish_markers(valid_grasps);

    // --- PHASE 3: LOGGING TO DISK ---
    const char *home_env = std::getenv("HOME");
    std::string home_path = home_env ? home_env : "/tmp";
    std::string log_dir = home_path + "/grasp_planner/logs";
    std::string log_file = log_dir + "/grasps.csv";
    try {
      if (!std::filesystem::exists(log_dir)) {
        std::filesystem::create_directories(log_dir);
      }

      bool file_exists = std::filesystem::exists(log_file);
      std::ofstream csv(log_file, std::ios::app);

      if (!file_exists) {
        csv << "Timestamp,Object,Quality,PositionX,PositionY,PositionZ,"
               "OrientationW,OrientationX,OrientationY,OrientationZ\n";
      }

      for (const auto &vg : valid_grasps) {
        csv << this->now().seconds() << "," << request->object_model_path << ","
            << vg.quality << "," << vg.pose.position.x << ","
            << vg.pose.position.y << "," << vg.pose.position.z << ","
            << vg.pose.orientation.w << "," << vg.pose.orientation.x << ","
            << vg.pose.orientation.y << "," << vg.pose.orientation.z << "\n";
      }
      csv.close();
      RCLCPP_INFO(this->get_logger(), "Logged %zu grasps to %s",
                  valid_grasps.size(), log_file.c_str());
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Failed to log grasps: %s", e.what());
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

// NEW: Iterates all robot nodes and publishes their meshes to RViz
void GraspPlannerService::publish_robot_visuals(
    VirtualRobot::RobotPtr robot_ptr) {
  if (!robot_ptr)
    return;

  visualization_msgs::msg::MarkerArray markers;
  int id = 1000; // Offset IDs to avoid conflict with grasps

  std::vector<VirtualRobot::RobotNodePtr> nodes = robot_ptr->getRobotNodes();
  int viz_count = 0;
  for (const auto &node : nodes) {
    if (node->getVisualization()) {
      viz_count++;
      // Create marker for this specific link (using its global pose inside
      // helper)
      auto marker = conversions::createMeshMarker(node, "robot_visuals", id++,
                                                  0.8, 0.8, 0.8, this->now());

      if (!marker.points.empty()) {
        markers.markers.push_back(marker);
      }
    }
  }
  markers_pub_->publish(markers);
  RCLCPP_INFO(this->get_logger(),
              "Published robot visuals. Total Nodes: %zu, With Viz: %d. Marker "
              "Count: %zu",
              nodes.size(), viz_count, markers.markers.size());
}

void GraspPlannerService::publish_object_marker(
    const Eigen::Matrix4f &object_pose) {
  visualization_msgs::msg::MarkerArray markers;

  // Use the new Mesh Bridge for the object too
  if (object) {
    auto mesh_marker = conversions::createMeshMarker(
        object, "object_mesh", 0, 0.0, 1.0, 0.0, this->now());

    // Override alpha for transparency
    mesh_marker.color.a = 0.8;

    if (!mesh_marker.points.empty()) {
      markers.markers.push_back(mesh_marker);
    }
  }

  markers_pub_->publish(markers);
}

void GraspPlannerService::publish_markers(
    const std::vector<ValidGrasp> &grasps) {
  visualization_msgs::msg::MarkerArray markers;
  int id = 1; // Start ID after object

  // Publish Grasp Markers (Arrows)
  for (const auto &vg : grasps) {
    visualization_msgs::msg::Marker arrow;
    arrow.header.frame_id = "world";
    arrow.header.stamp = this->now();
    arrow.ns = "grasps";
    arrow.id = id++;
    arrow.type = visualization_msgs::msg::Marker::ARROW;
    arrow.action = visualization_msgs::msg::Marker::ADD;

    arrow.pose = vg.pose;

    // Arrow size
    arrow.scale.x = 0.1;  // Length
    arrow.scale.y = 0.01; // Shaft diameter
    arrow.scale.z = 0.01; // Head diameter

    // Color based on quality (Green = High, Red = Low)
    arrow.color.r = 1.0 - vg.quality;
    arrow.color.g = vg.quality;
    arrow.color.b = 0.0;
    arrow.color.a = 1.0;

    markers.markers.push_back(arrow);
  }

  markers_pub_->publish(markers);
  RCLCPP_INFO(this->get_logger(), "Published %zu grasp markers",
              markers.markers.size());
}

} // namespace grasp_planner_service
