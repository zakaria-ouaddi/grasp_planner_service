#include "grasp_planner_service/grasp_planner_service.hpp"
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executors/multi_threaded_executor.hpp>

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    
    // Multi-threaded executor for parallel processing
    rclcpp::executors::MultiThreadedExecutor executor;
    auto node = std::make_shared<grasp_planner_service::GraspPlannerService>();
    
    RCLCPP_INFO(node->get_logger(), 
                "Starting Grasp Planner Service (MultiThreaded)");
    executor.add_node(node);
    executor.spin();
    
    rclcpp::shutdown();
    return 0;
}

