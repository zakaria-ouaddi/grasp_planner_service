#include "grasp_planner_service/grasp_planner_service.hpp"
#include <rclcpp/executors/multi_threaded_executor.hpp>
#include <rclcpp/rclcpp.hpp>

/**
 * @brief Main entry point for the Grasp Planner Service node.
 *
 * Origin: Standard ROS 2 Boilerplate.
 * Method: 1. Initializes the ROS 2 system.
 *         2. Creates a MultiThreadedExecutor to allow concurrent callback
 * processing.
 *         3. Instantiates the GraspPlannerService node.
 *         4. Adds the node to the executor and starts spinning.
 * Context: We use a MultiThreadedExecutor to ensure that service callbacks
 * (which might be long-running due to complex IK/Planning calculations) don't
 * block other potential callbacks (like TF listeners). Although currently the
 * node primarily handles one serial service, this sets up the architecture for
 * future parallel query handling.
 */
int main(int argc, char **argv) {
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
