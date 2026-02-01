#ifndef CONVERSION_HELPERS_HPP
#define CONVERSION_HELPERS_HPP

#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include <rclcpp/rclcpp.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <VirtualRobot/SceneObject.h>
#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/Visualization/TriMeshModel.h>
#include <VirtualRobot/Visualization/Visualization.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>

namespace grasp_planner_service {
namespace conversions {

/**
 * @brief Converts an Eigen::Matrix4f (Simox mm) to a geometry_msgs::msg::Pose
 * (ROS m).
 *
 * Origin: Custom Helper.
 * Method: 1. Extracts translation and divides by 1000.0 to convert millimeters
 * to meters.
 *         2. Extracts rotation matrix, converts to quaternion, and normalizes
 * it. Context: Simox uses millimeters for all internal units, while ROS uses
 * meters. This conversion is essential when passing data from the planner to
 * ROS messages.
 *
 * Args:
 *   eigen_pose: 4x4 Transformation Matrix in mm.
 * Returns:
 *   ROS Pose in meters.
 */
inline geometry_msgs::msg::Pose
eigenToRosPose(const Eigen::Matrix4f &eigen_pose) {
  geometry_msgs::msg::Pose ros_pose;
  // Convert mm to m
  ros_pose.position.x = eigen_pose(0, 3) / 1000.0f;
  ros_pose.position.y = eigen_pose(1, 3) / 1000.0f;
  ros_pose.position.z = eigen_pose(2, 3) / 1000.0f;

  Eigen::Matrix3f rotation = eigen_pose.block<3, 3>(0, 0);
  // Ensure rotation matrix is normalized before conversion
  Eigen::Quaternionf quat(rotation);
  quat.normalize();

  ros_pose.orientation.x = quat.x();
  ros_pose.orientation.y = quat.y();
  ros_pose.orientation.z = quat.z();
  ros_pose.orientation.w = quat.w();
  return ros_pose;
}

/**
 * @brief Converts a geometry_msgs::msg::Pose (ROS m) to an Eigen::Matrix4f
 * (Simox mm).
 *
 * Origin: Custom Helper.
 * Method: 1. Multiplies position by 1000.0 to convert meters to millimeters.
 *         2. Converts quaternion to rotation matrix.
 * Context: Required when receiving user requests (in ROS meters) and preparing
 * them for Simox algorithms (which expect millimeters).
 *
 * Args:
 *   ros_pose: ROS Pose in meters.
 * Returns:
 *   4x4 Transformation Matrix in mm.
 */
inline Eigen::Matrix4f
rosPoseToEigen(const geometry_msgs::msg::Pose &ros_pose) {
  Eigen::Matrix4f eigen_pose = Eigen::Matrix4f::Identity();
  // Convert m to mm
  eigen_pose(0, 3) = ros_pose.position.x * 1000.0f;
  eigen_pose(1, 3) = ros_pose.position.y * 1000.0f;
  eigen_pose(2, 3) = ros_pose.position.z * 1000.0f;

  Eigen::Quaternionf quat(ros_pose.orientation.w, ros_pose.orientation.x,
                          ros_pose.orientation.y, ros_pose.orientation.z);
  quat.normalize();
  eigen_pose.block<3, 3>(0, 0) = quat.toRotationMatrix();
  return eigen_pose;
}

/**
 * @brief Creates a TRIANGLE_LIST marker from a Simox SceneObject's geometry.
 *
 * Origin: Custom Helper (Bridge between Simox and ROS Visualization).
 * Method: 1. Accesses the `TriMeshModel` from the Simox object.
 *         2. Iterates through all faces of the mesh.
 *         3. Transforms each vertex by the object's global pose to get world
 * coordinates.
 *         4. Converts vertex units from mm to meters.
 *         5. Pushes transformed vertices into a `TRIANGLE_LIST` ROS Marker.
 * Context: Essential for Phase 3 Visualization. Since RViz cannot load Simox
 * XML models directly, we extract the mesh geometry programmatically and send
 * it as a raw mesh marker.
 *
 * Args:
 *   sceneObject: Pointer to the Simox object containing visual data.
 *   ns: Namespace for the marker.
 *   id: ID for the marker.
 *   r, g, b: Color components (0.0 - 1.0).
 *   now: Timestamp for the marker.
 * Returns:
 *   Complete visualization_msgs::msg::Marker ready to be published.
 */
inline visualization_msgs::msg::Marker
createMeshMarker(VirtualRobot::SceneObjectPtr sceneObject,
                 const std::string &ns, int id, float r, float g, float b,
                 rclcpp::Time now) {
  visualization_msgs::msg::Marker marker;
  marker.header.frame_id = "world";
  marker.header.stamp = now;
  marker.ns = ns;
  marker.id = id;
  marker.type = visualization_msgs::msg::Marker::TRIANGLE_LIST;
  marker.action = visualization_msgs::msg::Marker::ADD;

  // Scale is 1.0 because we put actual vertex positions
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  marker.color.r = r;
  marker.color.g = g;
  marker.color.b = b;
  marker.color.a = 1.0;

  // Safety check
  if (!sceneObject || !sceneObject->getVisualization() ||
      !sceneObject->getVisualization()->getTriMeshModel()) {
    return marker;
  }

  VirtualRobot::TriMeshModelPtr mesh =
      sceneObject->getVisualization()->getTriMeshModel();
  Eigen::Matrix4f globalPose = sceneObject->getGlobalPose();

  // Iterate faces and add vertices
  // Origin: Simox TriMeshModel Data Structure
  for (const auto &face : mesh->faces) {
    // Simox stores vertices in a vector, faces store indices
    if (face.id1 < mesh->vertices.size() && face.id2 < mesh->vertices.size() &&
        face.id3 < mesh->vertices.size()) {
      Eigen::Vector3f v1 = mesh->vertices[face.id1];
      Eigen::Vector3f v2 = mesh->vertices[face.id2];
      Eigen::Vector3f v3 = mesh->vertices[face.id3];

      // Transform to World Frame (mm to meters)
      // 1. Transform vertex by Object Pose
      Eigen::Vector3f v1_global = (globalPose * v1.homogeneous()).head<3>();
      Eigen::Vector3f v2_global = (globalPose * v2.homogeneous()).head<3>();
      Eigen::Vector3f v3_global = (globalPose * v3.homogeneous()).head<3>();

      geometry_msgs::msg::Point p1, p2, p3;
      p1.x = v1_global.x() / 1000.0;
      p1.y = v1_global.y() / 1000.0;
      p1.z = v1_global.z() / 1000.0;
      p2.x = v2_global.x() / 1000.0;
      p2.y = v2_global.y() / 1000.0;
      p2.z = v2_global.z() / 1000.0;
      p3.x = v3_global.x() / 1000.0;
      p3.y = v3_global.y() / 1000.0;
      p3.z = v3_global.z() / 1000.0;

      marker.points.push_back(p1);
      marker.points.push_back(p2);
      marker.points.push_back(p3);
    }
  }
  return marker;
}

} // namespace conversions
} // namespace grasp_planner_service

#endif // CONVERSION_HELPERS_HPP
