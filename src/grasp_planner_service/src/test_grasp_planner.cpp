#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

class GraspPlannerTester : public rclcpp::Node {
public:
  GraspPlannerTester() : Node("grasp_planner_tester") {
    // Dynamic path construction using HOME environment variable
    std::string home_dir = std::getenv("HOME");
    std::string default_robot_path =
        home_dir + "/grasp_planner/grasp_test_files/ArmarIII-RightArm.xml";
    std::string default_object_path =
        home_dir + "/grasp_planner/grasp_test_files/objects/WaterBottle.xml";

    // Initialize with dynamic defaults
    this->declare_parameter("robot_model_path", default_robot_path);
    this->declare_parameter("object_model_path", default_object_path);

    this->declare_parameter("end_effector_name", "Hand R");
    this->declare_parameter("kinematic_chain_name", "RightArm");
    this->declare_parameter("preshape_name", "Power Preshape");
    this->declare_parameter("object_pose_x", 0.5);
    this->declare_parameter("object_pose_y", 0.2);
    this->declare_parameter("object_pose_z", 0.2);

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

    // Ensure paths are not empty
    if (request->robot_model_path.empty()) {
      RCLCPP_ERROR(get_logger(), "Robot model path is empty!");
      return;
    }
    if (request->object_model_path.empty()) {
      RCLCPP_ERROR(get_logger(), "Object model path is empty!");
      return;
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

    // Real-world settings: Higher threshold for robust grasps
    request->quality_threshold = 0.05;
    request->timeout_ms = 30000;       // Very long timeout
    request->num_grasps_to_plan = 100; // Increased count

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
