// src/grasp_planner_service_node.cpp
#include "grasp_planner_service/grasp_planner_service.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    // Spin the node to handle callbacks
    rclcpp::spin(std::make_shared<GraspPlannerService>());

    rclcpp::shutdown();
    return 0;
}
