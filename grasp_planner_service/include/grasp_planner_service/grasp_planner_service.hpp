#ifndef GRASP_PLANNER_SERVICE_HPP
#define GRASP_PLANNER_SERVICE_HPP

#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <string>
#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2_ros/transform_broadcaster.h"

// Simox includes
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspStudio.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/XML/RobotIO.h>

// Include the new conversion helpers
#include "grasp_planner_service/conversion_helpers.hpp"

namespace grasp_planner_service {

class GraspPlannerService : public rclcpp::Node {
  public:
    GraspPlannerService();
    ~GraspPlannerService() = default;

  private:
    /**
     * @brief Callback function for handling grasp planning service requests
     */
    void handle_service(
        const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request>
            request,
        std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response);

    // ROS interfaces
    rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;

    // --- Components for future phases (Phase 2 & 3) ---
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr grasps_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr markers_pub_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

    // State for future reachability checks (Phase 2)
    sensor_msgs::msg::JointState current_joint_state_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP

