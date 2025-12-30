# Phase 2: Grasp Quality & Reachability

## Overview
In Phase 2,I enhanced the grasp planner to be more robust and practical. The goal was to ensure that generated grasps are not only theoretically stable (force closure) but also **reachable** by the robot's arm and **collision-free**.I also added ranking to prioritize the best grasps.

## What I Did

### 1. Enhanced Service Definition
I updated `PlanGrasp.srv` to support more complex queries:
- **New Inputs**:
    - `kinematic_chain_name`: The name of the robot's kinematic chain (e.g., "LeftArm") to use for Inverse Kinematics (IK).
    - `object_pose`: The actual pose of the object in the world, allowing us to plan for objects at specific locations.
    - `num_grasps_to_plan`: Limit on how many grasps to generate.
- **New Outputs**:
    - `qualities`: Array of quality scores for each grasp.
    - `are_force_closure`: Boolean array indicating if each grasp is force closure.

### 2. Reachability (Inverse Kinematics)
I integrated `VirtualRobot::DifferentialIK` into the service.
- For each generated grasp, we check if the robot's arm (specified by `kinematic_chain_name`) can reach the grasp pose.
- If IK fails, the grasp is discarded or marked as unreachable.

### 3. Collision Detection
I integrated `VirtualRobot::CDManager` (Collision Detection Manager).
- We check for collisions between the robot (gripper and arm) and the object/environment during the grasp.
- This ensures we don't plan grasps that would cause the robot to crash into the object or itself.

### 4. Grasp Ranking
- I implemented logic to sort the valid grasps based on their quality score (Simox grasp quality).
- The service now returns the "best" grasps first.

## Challenges & Solutions

### Coordinate System Mismatch (Units)
- **Issue**: Simox/VirtualRobot typically uses **millimeters**, while ROS uses **meters**. This caused the robot to try to reach targets that were 1000x too close or too far, or the object to appear huge/tiny.
- **Solution**: I implemented unit conversion helpers. When receiving the `object_pose` from ROS (meters), we convert it to Simox format (millimeters) before planning. When returning grasp poses to ROS, we convert back to meters.

### IK Solver Failures
- **Issue**: The Differential IK solver would sometimes fail to find a solution even for reachable poses, or get stuck in local minima.
- **Solution**: I adjusted the IK parameters (steps, loops) and ensured the initial configuration was reasonable. We also accepted that not all grasps are reachable and simply filtered those out.

### Data Type Conversion
- **Issue**: Converting between ROS `geometry_msgs::Pose` and Eigen matrices (used by Simox) was repetitive and error-prone.
- **Solution**: I created a `conversion_helpers.hpp` file with `rosPoseToEigen` and `eigenToRosPose` functions to handle this cleanly and consistently.

## How to Run Phase 2

### 1. Build
```bash
colcon build --packages-select grasp_planner_msgs grasp_planner_service
source install/setup.bash
```

### 2. Run the Service
```bash
ros2 run grasp_planner_service grasp_planner_service
```

### 3. Run the Test Client
The test client was updated to send an object pose.
```bash
ros2 run grasp_planner_service test_grasp_planner
```
*Note: You can now modify the `test_grasp_planner.cpp` or use ROS parameters (if implemented) to change the target object pose and see if the robot can reach it.*
