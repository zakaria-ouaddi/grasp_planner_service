# Grasp Planner Service: Phase Change Log

This document tracks the modifications made to each file across the different development phases.

## Phase 1: Core Integration & API Development
**Goal:** Establish the basic service infrastructure to generate grasps using Simox/GraspStudio.

### `grasp_planner_msgs/srv/PlanGrasp.srv`
- **Created**: Defined the basic service interface.
- **Fields**: `robot_model_path`, `object_model_path`, `end_effector_name`, `preshape_name`, `quality_threshold`, `timeout_ms`.

### `grasp_planner_service/src/grasp_planner_service.cpp`
- **Created**: Implemented the core ROS 2 node.
- **Features**:
    - Loaded Robot and Object XML files using `VirtualRobot`.
    - Initialized `GraspStudio::GraspQualityMeasureWrenchSpace` (Force Closure).
    - Initialized `GraspStudio::ApproachMovementSurfaceNormal`.
    - Implemented the `GraspStudio::GenericGraspPlanner` loop to generate candidate grasps.

### `grasp_planner_service/src/test_grasp_planner.cpp`
- **Created**: A simple test client node.
- **Features**: Hardcoded parameters to call the service and print the result (success/failure).

---

## Phase 2: Grasp Quality & Reachability
**Goal:** Filter grasps to ensure they are reachable by the robot arm and collision-free, and rank them by quality.

### `grasp_planner_msgs/srv/PlanGrasp.srv`
- **Modified**:
    - Added `kinematic_chain_name` (string) for IK checks.
    - Added `object_pose` (geometry_msgs/Pose) to define where the object is.
    - Added `num_grasps_to_plan` (int32).
    - Changed response fields to arrays: `qualities[]`, `grasp_poses[]`, `are_force_closure[]`.

### `grasp_planner_service/src/grasp_planner_service.cpp`
- **Modified**:
    - **Reachability**: Integrated `VirtualRobot::DifferentialIK` to check if the arm can reach the grasp pose.
    - **Collision**: Integrated `VirtualRobot::CDManager` to check for self-collisions during the grasp.
    - **Ranking**: Added logic to sort valid grasps by their quality score (descending).
    - **Pose Conversion**: Added helper functions to convert between ROS Poses and Eigen Matrices (Simox format).

### `grasp_planner_service/src/test_grasp_planner.cpp`
- **Modified**:
    - Updated to populate the new `object_pose` field.
    - Added ROS parameters to allow dynamic configuration (e.g., changing object position or robot model without recompiling).

---

## Phase 3: Visualization & Debugging Tools
**Goal:** Visualize the object, the planned grasps, and the robot context in RViz.

### `grasp_planner_service/package.xml`
- **Modified**: Added dependencies:
    - `visualization_msgs`
    - `tf2_ros`
    - `tf2_eigen`

### `grasp_planner_service/CMakeLists.txt`
- **Modified**: Found and linked the new dependencies (`visualization_msgs`, `tf2_ros`, `tf2_eigen`).

### `grasp_planner_service/include/grasp_planner_service/grasp_planner_service.hpp`
- **Modified**:
    - Added `rclcpp::Publisher<visualization_msgs::msg::MarkerArray>` for publishing markers.
    - Added `tf2_ros::TransformBroadcaster` for publishing the object frame.
    - Added `ValidGrasp` struct definition.
    - Added `publish_markers` function declaration.

### `grasp_planner_service/src/grasp_planner_service.cpp`
- **Modified**:
    - **TF Broadcasting**: Added logic to broadcast a transform from `world` -> `object_frame` based on the request pose.
    - **Marker Publishing**: Implemented `publish_markers` to draw:
        - A **Cube** marker representing the object.
        - **Arrow** markers representing each valid grasp (Green = High Quality, Red = Low Quality).
    - **Initialization**: Initialized the new publisher and broadcaster in the constructor.

### `grasp_planner_service/include/grasp_planner_service/conversion_helpers.hpp`
- **Modified**:
    - Added **Unit Scaling**: Simox uses millimeters (mm), while ROS uses meters (m).
    - `rosPoseToEigen`: Multiplies position by 1000.0.
    - `eigenToRosPose`: Divides position by 1000.0.

### `grasp_planner_service/src/test_grasp_planner.cpp`
- **Modified**: Updated default object pose parameters to use **Meters** (e.g., 0.5) instead of Millimeters (500.0) to match the new scaling logic.

### `grasp_planner_service/config/grasp_planner.rviz`
- **New File**: Created a default RViz configuration file pre-configured to show the `grasp_markers` topic and the `world` frame.
