#include "grasp_planner_service/grasp_planner_service.hpp"
#include <geometry_msgs/msg/pose.hpp>
#include <Eigen/Geometry>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/XML/RobotIO.h>
//#include <GraspPlanning/GraspQuality/GraspQualityMeasure.h> 
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h> 
namespace grasp_planner_service {

GraspPlannerService::GraspPlannerService()
    : Node("grasp_planner_service"),
      robot(nullptr),
      eefCloned(nullptr),
      object(nullptr),
      eef(nullptr),
      grasps(nullptr),
      qualityMeasure(nullptr),
      approach(nullptr),
      planner(nullptr)
{
    service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
        "plan_grasp",
        std::bind(&GraspPlannerService::handle_service, this,
                 std::placeholders::_1, std::placeholders::_2));
    RCLCPP_INFO(this->get_logger(), "Grasp Planner Service initialized");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) 
{
    RCLCPP_INFO(this->get_logger(), "Received grasp planning request for %s",
               request->object_model_path.c_str());

    try {
        // Load the robot model
        robot = VirtualRobot::RobotIO::loadRobot(request->robot_model_path);
        if (!robot) {
            response->success = false;
            RCLCPP_ERROR(this->get_logger(), "Failed to load robot model: %s",
                        request->robot_model_path.c_str());
            return;
        }

        // Get end effector
        eef = robot->getEndEffector(request->end_effector_name);
        if (!eef) {
            response->success = false;
            RCLCPP_ERROR(this->get_logger(), "End effector '%s' not found",
                        request->end_effector_name.c_str());
            return;
        }

        // Set preshape if specified
        if (!request->preshape_name.empty()) {
            eef->setPreshape(request->preshape_name);
        }

        // Load object model
        object = VirtualRobot::ObjectIO::loadManipulationObject(request->object_model_path);
        if (!object) {
            response->success = false;
            RCLCPP_ERROR(this->get_logger(), "Failed to load object model");
            return;
        }

        // Initialize grasp planning components
        qualityMeasure.reset(new GraspStudio::GraspQualityMeasureWrenchSpace(object));
        qualityMeasure->calculateObjectProperties();
        
        approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(object, eef, request->preshape_name));
        eefCloned = approach->getEEFRobotClone();

        // Create new grasp set
        grasps.reset(new VirtualRobot::GraspSet(
            "ros_planned_grasps", robot->getType(), eef->getName()));

        // Setup planner with quality threshold and force closure requirement
        planner.reset(new GraspStudio::GenericGraspPlanner(
            grasps, qualityMeasure, approach, request->quality_threshold, true));
        planner->setVerbose(true);

        // Plan grasps with timeout
        int grasps_planned = planner->plan(1, request->timeout_ms);
        if (grasps_planned <= 0 || grasps->getSize() == 0) {
            response->success = false;
            RCLCPP_WARN(this->get_logger(), "No valid grasps found");
            return;
        }

        // Get the best grasp (first in list)
        VirtualRobot::GraspPtr best_grasp = grasps->getGrasp(0);
        
        // Get global TCP pose for the grasp
        Eigen::Matrix4f global_tcp_pose = best_grasp->getTcpPoseGlobal(object->getGlobalPose());
        
        // Convert to ROS pose
        response->grasp_pose.position.x = global_tcp_pose(0, 3);
        response->grasp_pose.position.y = global_tcp_pose(1, 3);
        response->grasp_pose.position.z = global_tcp_pose(2, 3);
        
        Eigen::Matrix3f rotation = global_tcp_pose.block<3, 3>(0, 0);
        Eigen::Quaternionf quat(rotation);
        response->grasp_pose.orientation.x = quat.x();
        response->grasp_pose.orientation.y = quat.y();
        response->grasp_pose.orientation.z = quat.z();
        response->grasp_pose.orientation.w = quat.w();

        // Set quality metrics
        response->quality = qualityMeasure->getGraspQuality();
        response->is_force_closure = qualityMeasure->isGraspForceClosure();
        response->success = true;

        RCLCPP_INFO(this->get_logger(), 
                   "Found grasp with quality %.2f (force closure: %d)",
                   response->quality, response->is_force_closure);

    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Exception during grasp planning: %s",
                    e.what());
        response->success = false;
    }
}

} // namespace grasp_planner_service
