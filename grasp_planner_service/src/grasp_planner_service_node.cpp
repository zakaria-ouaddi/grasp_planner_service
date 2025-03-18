// src/grasp_planner_service_node.cpp
#include "grasp_planner_service/grasp_planner_service.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<grasp_planner_service::GraspPlannerService>();

    // Spin the node to handle callbacks
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
