#ifndef CONVERSION_HELPERS_HPP
#define CONVERSION_HELPERS_HPP

#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace grasp_planner_service {
namespace conversions {

/**
 * @brief Converts an Eigen::Matrix4f (Simox mm) to a geometry_msgs::msg::Pose
 * (ROS m)
 */
inline geometry_msgs::msg::Pose
eigenToRosPose(const Eigen::Matrix4f &eigen_pose) {
  geometry_msgs::msg::Pose ros_pose;
  // Convert mm to m
  ros_pose.position.x = eigen_pose(0, 3);
  ros_pose.position.y = eigen_pose(1, 3);
  ros_pose.position.z = eigen_pose(2, 3);

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
 * (Simox mm)
 */
inline Eigen::Matrix4f
rosPoseToEigen(const geometry_msgs::msg::Pose &ros_pose) {
  Eigen::Matrix4f eigen_pose = Eigen::Matrix4f::Identity();
  // Convert m to mm
  eigen_pose(0, 3) = ros_pose.position.x;
  eigen_pose(1, 3) = ros_pose.position.y;
  eigen_pose(2, 3) = ros_pose.position.z;

  Eigen::Quaternionf quat(ros_pose.orientation.w, ros_pose.orientation.x,
                          ros_pose.orientation.y, ros_pose.orientation.z);
  quat.normalize();
  eigen_pose.block<3, 3>(0, 0) = quat.toRotationMatrix();
  return eigen_pose;
}

} // namespace conversions
} // namespace grasp_planner_service

#endif // CONVERSION_HELPERS_HPP
