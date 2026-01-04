#include "grasp_planner_service/conversion_helpers.hpp"
#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>

// Test Fixture
class ConversionTest : public ::testing::Test {
protected:
  void SetUp() override {}
};

using namespace grasp_planner_service;

// 1. Identity Transform Test
TEST_F(ConversionTest, IdentityTransform) {
  geometry_msgs::msg::Pose ros_pose;
  ros_pose.position.x = 0;
  ros_pose.position.y = 0;
  ros_pose.position.z = 0;
  ros_pose.orientation.w = 1;
  ros_pose.orientation.x = 0;
  ros_pose.orientation.y = 0;
  ros_pose.orientation.z = 0;

  Eigen::Matrix4f mat = conversions::rosPoseToEigen(ros_pose);

  // Check diagonals are 1
  EXPECT_NEAR(mat(0, 0), 1.0, 1e-5);
  EXPECT_NEAR(mat(1, 1), 1.0, 1e-5);
  EXPECT_NEAR(mat(2, 2), 1.0, 1e-5);

  // Check translation is 0
  EXPECT_NEAR(mat(0, 3), 0.0,
              1e-5); // Divide by 1000? No, helper assumes meters now
}

// 2. Translation Test (Meters to Millimeters handling)
// Note: Simox uses millimeters internally. The helper currently does strict
// copy. We need to confirm if our helper does scaling or if that handled
// elsewhere. Looking at the helper code: "mat(0, 3) = pose.position.x *
// 1000.0f;"
TEST_F(ConversionTest, TranslationScaling) {
  geometry_msgs::msg::Pose ros_pose;
  ros_pose.position.x = 1.0;  // 1 meter
  ros_pose.position.y = 0.5;  // 0.5 meters
  ros_pose.position.z = -0.2; // -0.2 meters
  ros_pose.orientation.w = 1;

  Eigen::Matrix4f mat = conversions::rosPoseToEigen(ros_pose);

  // Expect 1000mm, 500mm, -200mm
  EXPECT_NEAR(mat(0, 3), 1000.0, 1e-5);
  EXPECT_NEAR(mat(1, 3), 500.0, 1e-5);
  EXPECT_NEAR(mat(2, 3), -200.0, 1e-5);
}

// 3. Rotation Test (90 degrees around Z)
TEST_F(ConversionTest, RotationZ90) {
  geometry_msgs::msg::Pose ros_pose;
  // 90 deg around Z = (0, 0, 0.707, 0.707)
  ros_pose.orientation.w = 0.7071068;
  ros_pose.orientation.z = 0.7071068;

  Eigen::Matrix4f mat = conversions::rosPoseToEigen(ros_pose);

  // X axis should point to Y
  EXPECT_NEAR(mat(0, 0), 0.0, 1e-4);
  EXPECT_NEAR(mat(1, 0), 1.0, 1e-4);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
