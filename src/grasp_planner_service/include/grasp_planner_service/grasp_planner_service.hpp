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
// Origin: Simox (https://gitlab.com/simox/simox)
// These libraries provide the core functionalities for grasp planning, robot
// kinematics, and 3D geometry.
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

/**
 * @brief Service node for planning grasps on 3D objects using Simox.
 *
 * Origin: Custom ROS 2 Node.
 * Method: This node integrates the Simox GraspStudio library into ROS 2.
 *         It loads robot and object models from XML files, generates candidate
 * grasps using Simox's approach movement and quality measures, and filters them
 *         based on reachability and collision checks.
 * Context: Used as the primary High-Level Planning capability in the Grasp
 * Planner project.
 */
class GraspPlannerService : public rclcpp::Node {
public:
  // Constructor: Initializes ROS interfaces (Simox components are initialized
  // per request).
  GraspPlannerService();
  ~GraspPlannerService() = default;

private:
  /**
   * @brief Callback function for handling grasp planning service requests.
   *
   * Method: This is the main orchestration logic.
   *         1. Loads Simox models.
   *         2. Plans grasps using GenericGraspPlanner.
   *         3. Filters grasps for reachability (IK) and collisions.
   *         4. Publishes visualization markers.
   *
   * Args:
   *   request: The service request containing model paths and parameters.
   *   response: The service response to be filled with grasp poses.
   */
  void handle_service(
      const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request>
          request,
      std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response);

  // Internal struct to hold grasp data along with its computed quality and ROS
  // pose.
  struct ValidGrasp {
    // Origin: Simox VirtualRobot::Grasp
    VirtualRobot::GraspPtr grasp;
    // Origin: Computed by GraspStudio
    float quality;
    // Origin: Converted from Simox Eigen::Matrix4f to ROS geometry_msgs::Pose
    geometry_msgs::msg::Pose pose;
  };

  // ROS interfaces
  rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;

  // --- Components for future phases (Phase 2 & 3) ---

  // Persistent pointers for visualization
  // Origin: Simox VirtualRobot
  // Why: Storing these allows us to access the visualization meshes needed for
  // RViz markers.
  VirtualRobot::RobotPtr robot;
  VirtualRobot::ManipulationObjectPtr object;

  /**
   * @brief Publishes visualization markers for the planned grasps.
   *
   * Method: Converts valid grasp poses into RViz Arrow markers.
   *         Green arrows indicate high quality, Red arrows indicate lower
   * quality.
   */
  void publish_markers(const std::vector<ValidGrasp> &grasps);

  /**
   * @brief Publishes visualization marker for the object.
   *
   * Method: Extracts the TriMeshModel from the Simox object and converts it
   *         to a TRIANGLE_LIST marker for RViz.
   */
  void publish_object_marker(const Eigen::Matrix4f &object_pose);

  /**
   * @brief Publishes visualization markers for the full robot structure.
   *
   * Method: Iterates through all robot nodes, extracts their visualization
   * meshes, and publishes them to RViz. This is necessary because RViz cannot
   *         natively load Simox XML robot models.
   */
  void publish_robot_visuals(VirtualRobot::RobotPtr robot_ptr);

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr
      markers_pub_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP
