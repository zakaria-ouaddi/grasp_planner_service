#include "grasp_planner_service/grasp_planner_service.hpp"
#include <Eigen/Geometry>
#include <VirtualRobot/Grasping/Grasp.h> 

namespace grasp_planner_service {

// This constructor is now correct. It no longer initializes
// the Simox variables that we removed from the header.
GraspPlannerService::GraspPlannerService()
    : Node("grasp_planner_service")
{
    service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
        "plan_grasp",
        std::bind(&GraspPlannerService::handle_service, this,
                  std::placeholders::_1, std::placeholders::_2));
                  
    // TODO: Initialize publishers/subscribers for future phases here

    RCLCPP_INFO(this->get_logger(), "Grasp Planner Service (Phase 1) initialized");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) 
{
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
            response->error_message = "Failed to load robot model: " + request->robot_model_path;
            RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
            return;
        }

        // 2. Get end effector
        eef = robot->getEndEffector(request->end_effector_name);
        if (!eef) {
            response->success = false;
            response->error_message = "End effector '" + request->end_effector_name + "' not found";
            RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
            return;
        }

        // 3. Set preshape if specified
        if (!request->preshape_name.empty()) {
            if (eef->hasPreshape(request->preshape_name)) {
                eef->setPreshape(request->preshape_name);
            } else {
                response->success = false;
                response->error_message = "Preshape '" + request->preshape_name + "' not found";
                RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
                return;
            }
        }

        // 4. Load object model
        object = VirtualRobot::ObjectIO::loadManipulationObject(request->object_model_path);
        if (!object) {
            response->success = false;
            response->error_message = "Failed to load object model: " + request->object_model_path;
            RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
            return;
        }

        // 5. SET OBJECT POSE (Phase 1.1 Requirement)
        Eigen::Matrix4f eigen_object_pose = conversions::rosPoseToEigen(request->object_pose);
        object->setGlobalPose(eigen_object_pose);
        
        // 6. Initialize grasp planning components
        qualityMeasure.reset(new GraspStudio::GraspQualityMeasureWrenchSpace(object));
        qualityMeasure->calculateObjectProperties();
        
        approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(object, eef, request->preshape_name));

        // Create new grasp set
        grasps.reset(new VirtualRobot::GraspSet(
            "ros_planned_grasps", robot->getType(), eef->getName()));

        // Setup planner with quality threshold and force closure requirement (last param = true)
        planner.reset(new GraspStudio::GenericGraspPlanner(
            grasps, qualityMeasure, approach, request->quality_threshold, true));
        planner->setVerbose(false); // Set to true for detailed Simox logging

        // 7. PLAN GRASPS (Phase 1.1 Requirement)
        int grasps_planned = planner->plan(request->num_grasps_to_plan, request->timeout_ms);
        
        if (grasps_planned <= 0 || grasps->getSize() == 0) {
            response->success = false;
            response->error_message = "No valid grasps found";
            RCLCPP_WARN(this->get_logger(), "%s", response->error_message.c_str());
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Found %d grasps. Converting to ROS format.", grasps_planned);

        // 8. PROCESS GRASP LIST (Phase 1.1 Requirement)
        for (size_t i = 0; i < grasps->getSize(); ++i) {
            VirtualRobot::GraspPtr grasp = grasps->getGrasp(i);
            
            // Get global TCP pose for the grasp
            Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
            
            // Convert to ROS pose using helper (Phase 1.2)
            geometry_msgs::msg::Pose ros_grasp_pose = 
                conversions::eigenToRosPose(global_tcp_pose);

            // --- CORRECT: Add to response arrays ---
            response->grasp_poses.push_back(ros_grasp_pose);
            response->qualities.push_back(grasp->getQuality());

            // --- FIX: We requested force closure, so all found grasps have it ---
            response->are_force_closure.push_back(true);
        }

        response->success = true;
        response->error_message = "Successfully planned " + std::to_string(response->grasp_poses.size()) + " grasps.";
        RCLCPP_INFO(this->get_logger(), "%s", response->error_message.c_str());

    } 
    // 9. ERROR HANDLING (Phase 1.3 Requirement)
    catch (const VirtualRobot::VirtualRobotException& e) {
        response->success = false;
        response->error_message = std::string("Simox API Error: ") + e.what();
        RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
    } 
    catch (const std::exception &e) {
        response->success = false;
        response->error_message = std::string("Standard Exception: ") + e.what();
        RCLCPP_ERROR(this->get_logger(), "%s", response->error_message.c_str());
    }
}

} // namespace grasp_planner_service


