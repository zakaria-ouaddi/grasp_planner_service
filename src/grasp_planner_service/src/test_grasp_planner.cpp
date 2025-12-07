#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

class GraspPlannerTester : public rclcpp::Node {
public:
  GraspPlannerTester() : Node("grasp_planner_tester") {
    // Initialize with your actual file paths
    this->declare_parameter(
        "robot_model_path",
        "/home/zakaria/grasp_planner/grasp_test_files/ArmarIII-RightArm.xml");
    this->declare_parameter(
        "object_model_path",
        "/home/zakaria/grasp_planner/grasp_test_files/plate.xml");

    this->declare_parameter("end_effector_name", "Hand R");
    this->declare_parameter("kinematic_chain_name", "RightArm");
    this->declare_parameter("preshape_name", "");
    this->declare_parameter("object_pose_x", 500.0);
    this->declare_parameter("object_pose_y", 200.0);
    this->declare_parameter("object_pose_z", 200.0);

    client_ = create_client<grasp_planner_msgs::srv::PlanGrasp>("plan_grasp");

    // Call immediately on startup
    timer_ = create_wall_timer(std::chrono::seconds(1), [this]() {
      this->test_grasp_planning();
      // Do not shutdown here! Wait for callback.
      timer_->cancel(); // Stop the timer so it doesn't fire again
    });
  }

  void test_grasp_planning() {
    RCLCPP_INFO(get_logger(), "Waiting for service...");
    if (!client_->wait_for_service(std::chrono::seconds(3))) {
      RCLCPP_ERROR(get_logger(), "Service not available");
      return;
    }

    auto request =
        std::make_shared<grasp_planner_msgs::srv::PlanGrasp::Request>();

    // Get paths from parameters
    this->get_parameter("robot_model_path", request->robot_model_path);
    this->get_parameter("object_model_path", request->object_model_path);

    // Get other configuration from parameters
    this->get_parameter("end_effector_name", request->end_effector_name);
    this->get_parameter("kinematic_chain_name", request->kinematic_chain_name);
    this->get_parameter("preshape_name", request->preshape_name);

    // Hardcoded fallback (replace with your paths)
    if (request->robot_model_path.empty()) {
      request->robot_model_path =
          "/home/zakaria/grasp_planner/grasp_test_files/ArmarIII-RightArm.xml";
    }
    if (request->object_model_path.empty()) {
      request->object_model_path =
          "/home/zakaria/grasp_planner/grasp_test_files/plate.xml";
    }

    // Set object pose from parameters
    double x, y, z;
    this->get_parameter("object_pose_x", x);
    this->get_parameter("object_pose_y", y);
    this->get_parameter("object_pose_z", z);

    request->object_pose.position.x = x;
    request->object_pose.position.y = y;
    request->object_pose.position.z = z;
    request->object_pose.orientation.w = 1.0;

    request->quality_threshold = 0.001; // Lowered threshold
    request->timeout_ms = 30000;        // Very long timeout
    request->num_grasps_to_plan = 100;  // Increased count

    RCLCPP_INFO(get_logger(), "Sending request...");

    // Use async callback to avoid blocking/nested spin
    client_->async_send_request(
        request,
        [this](rclcpp::Client<grasp_planner_msgs::srv::PlanGrasp>::SharedFuture
                   future) {
          try {
            auto response = future.get();
            if (response->success && !response->grasp_poses.empty()) {
              RCLCPP_INFO(get_logger(), "Successfully found %zu grasps!",
                          response->grasp_poses.size());
              RCLCPP_INFO(get_logger(), "Best Grasp Pose: (%.2f, %.2f, %.2f)",
                          response->grasp_poses[0].position.x,
                          response->grasp_poses[0].position.y,
                          response->grasp_poses[0].position.z);
              RCLCPP_INFO(get_logger(), "Best Grasp Quality: %.3f",
                          response->qualities[0]);
              RCLCPP_INFO(get_logger(), "Force Closure: %s",
                          response->are_force_closure[0] ? "yes" : "no");
            } else {
              RCLCPP_ERROR(
                  get_logger(),
                  "Grasp planning failed or found no grasps. Error: %s",
                  response->error_message.c_str());
            }
          } catch (const std::exception &e) {
            RCLCPP_ERROR(get_logger(), "Service call failed: %s", e.what());
          }
          rclcpp::shutdown(); // Exit after response
        });
  }

private:
  rclcpp::Client<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GraspPlannerTester>());
  rclcpp::shutdown();
  return 0;
}
