#ifndef GRASP_PLANNER_SERVICE_HPP
#define GRASP_PLANNER_SERVICE_HPP

#include "geometry_msgs/msg/pose.hpp"
#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "visualization_msgs/msg/marker_array.hpp"

#include <memory>
#include <string>

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

  struct ValidGrasp {
    VirtualRobot::GraspPtr grasp;
    float quality;
    geometry_msgs::msg::Pose pose;
  };

  // ROS interfaces
  rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;

  // --- Components for future phases (Phase 2 & 3) ---

  // Persistent pointers for visualization
  VirtualRobot::RobotPtr robot;
  VirtualRobot::ManipulationObjectPtr object;

  /**
   * @brief Publishes visualization markers for the object and planned grasps
   */
  void publish_markers(const std::vector<ValidGrasp> &grasps);

  /**
   * @brief Publishes visualization marker for the object (uses member 'object')
   */
  void publish_object_marker(const Eigen::Matrix4f &object_pose);

  /**
   * @brief Publishes visualization markers for the full robot structure
   */
  void publish_robot_visuals(VirtualRobot::RobotPtr robot_ptr);

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr
      markers_pub_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP
