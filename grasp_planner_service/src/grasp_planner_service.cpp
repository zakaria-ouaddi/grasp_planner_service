// src/grasp_planner_service.cpp
#include "grasp_planner_service/grasp_planner_service.hpp"

namespace grasp_planner_service {

GraspPlannerService::GraspPlannerService() : Node("grasp_planner_service") {
    service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
        "plan_grasp", std::bind(&GraspPlannerService::handle_service, this,
                                std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Grasp Planner Service is ready");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) {
    RCLCPP_INFO(this->get_logger(), "Received grasp planning request for %s",
                request->object_model_path.c_str());

    try {
        // Load the robot and object models
        VirtualRobot::RobotPtr robot = loadRobot(request->robot_model_path);

        if (!robot) {
            response->success = false;
            RCLCPP_INFO(this->get_logger(), "Failed to load robot model: %s",
                        request->robot_model_path.c_str());
            return;
        }

        // Fill in the response with a dummy grasp pose
        response->grasp_pose.position.x = 0.0;
        response->grasp_pose.position.y = 0.0;
        response->grasp_pose.position.z = 0.0;
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Exception during grasp planning: %s",
                     e.what());
        response->success = false;
    }
}

VirtualRobot::RobotPtr
GraspPlannerService::loadRobot(const std::string &robot_model_path) {
    VirtualRobot::RobotPtr robot =
        VirtualRobot::RobotIO::loadRobot(robot_model_path);
    if (!robot) {
        RCLCPP_ERROR(this->get_logger(), "Failed to load robot model from: %s",
                     robot_model_path.c_str());
    }
    return robot;
}

VirtualRobot::ManipulationObjectPtr
GraspPlannerService::loadObject(const std::string &object_model_path) {

    VirtualRobot::ManipulationObjectPtr object =
        VirtualRobot::ObjectIO::loadManipulationObject(object_model_path);
    if (!object) {
        RCLCPP_ERROR(this->get_logger(), "Failed to load object model from: %s",
                     object_model_path.c_str());
    }
    return object;
}

} // namespace grasp_planner_service
