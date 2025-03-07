// src/grasp_planner_service.cpp
#include "grasp_planner_service/grasp_planner_service.hpp"

GraspPlannerService::GraspPlannerService() : Node("grasp_planner_service") {
    service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
        "plan_grasp", std::bind(&GraspPlannerService::handle_service, this,
                                std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Grasp Planner Service is ready");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) {
    RCLCPP_INFO(this->get_logger(), "Received grasp planning request");
}
