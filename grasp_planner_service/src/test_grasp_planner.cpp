#include "rclcpp/rclcpp.hpp"
#include "grasp_planner_msgs/srv/plan_grasp.hpp"

class GraspPlannerTester : public rclcpp::Node {
public:
    GraspPlannerTester() : Node("grasp_planner_tester") {
        // Initialize with your actual file paths
        this->declare_parameter("robot_model_path", "/home/zakaria/local/src/Simox/VirtualRobot/data/robots/ArmarIII/ArmarIII-RightHand.xml");
        this->declare_parameter("object_model_path", "/home/zakaria/local/src/Simox/VirtualRobot/data/objects/box.xml");
        
        client_ = create_client<grasp_planner_msgs::srv::PlanGrasp>("plan_grasp");
        
        // Call immediately on startup
        timer_ = create_wall_timer(
            std::chrono::seconds(1),
            [this]() {
                this->test_grasp_planning();
                rclcpp::shutdown();  // Exit after test
            });
    }

    void test_grasp_planning() {
        RCLCPP_INFO(get_logger(), "Waiting for service...");
        if (!client_->wait_for_service(std::chrono::seconds(3))) {
            RCLCPP_ERROR(get_logger(), "Service not available");
            return;
        }

        auto request = std::make_shared<grasp_planner_msgs::srv::PlanGrasp::Request>();
        
        // Get paths from parameters
        this->get_parameter("robot_model_path", request->robot_model_path);
        this->get_parameter("object_model_path", request->object_model_path);
        
        // Hardcoded fallback (replace with your paths)
        if (request->robot_model_path.empty()) {
            request->robot_model_path = "/home/zakaria/local/src/Simox/VirtualRobot/data/robots/ArmarIII/ArmarIII-RightHand.xml";
        }
        if (request->object_model_path.empty()) {
            request->object_model_path = "/home/zakaria/local/src/Simox/VirtualRobot/data/objects/box.xml";
        }

        request->end_effector_name = "Hand R";
        request->preshape_name = "Power Preshape";
        request->quality_threshold = 0.2;
        request->timeout_ms = 5000;  // Longer timeout for complex hands

        RCLCPP_INFO(get_logger(), "Sending request...");
        auto future = client_->async_send_request(request);

        if (rclcpp::spin_until_future_complete(shared_from_this(), future) !=
            rclcpp::FutureReturnCode::SUCCESS) {
            RCLCPP_ERROR(get_logger(), "Service call failed");
            return;
        }

        auto response = future.get();
        // NEW, CORRECTED CODE for test_grasp_planner.cpp
        if (response->success && !response->grasp_poses.empty()) {
            RCLCPP_INFO(get_logger(), "Successfully found %zu grasps!", response->grasp_poses.size());

            // Log details for the *first* (best) grasp
            RCLCPP_INFO(get_logger(), "Best Grasp Pose: (%.2f, %.2f, %.2f)",
                        response->grasp_poses[0].position.x,    // <-- Access [0]
                        response->grasp_poses[0].position.y,    // <-- Access [0]
                        response->grasp_poses[0].position.z);   // <-- Access [0]
                        
            RCLCPP_INFO(get_logger(), "Best Grasp Quality: %.3f", response->qualities[0]); // <-- Access [0]
            
            RCLCPP_INFO(get_logger(), "Force Closure: %s",
                        response->are_force_closure[0] ? "yes" : "no"); // <-- Access [0]
        } else {
            RCLCPP_ERROR(get_logger(), "Grasp planning failed or found no grasps.");
        }
    }

private:
    rclcpp::Client<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr client_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GraspPlannerTester>());
    rclcpp::shutdown();
    return 0;
}
