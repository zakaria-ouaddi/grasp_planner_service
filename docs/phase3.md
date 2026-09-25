# Phase 3: Visualization & Debugging Tools

## Overview
Phase 3 focuses on adding visualization capabilities to the grasp planner service to aid in debugging and verification. It introduces RViz markers for the object and planned grasps, TF broadcasting for the object frame, and proper unit scaling between Simox (millimeters) and ROS (meters).

## Key Features

### 1. Visualization Markers
- **Object Marker**: A blue cube representing the object pose is published to the `/grasp_markers` topic.
- **Grasp Markers**: Arrows representing the planned grasp poses are published to the `/grasp_markers` topic.
    - **Color Coding**: Arrows are colored based on grasp quality (Green = High Quality, Red = Low Quality).
    - **Scale**: Arrows are scaled for visibility.

### 2. TF Broadcasting
- The service now broadcasts a transform from `world` to `object_frame` using `tf2_ros::TransformBroadcaster`.
- This allows RViz to correctly visualize the object and grasps relative to the world frame.

### 3. Unit Scaling
- **Simox**: Uses millimeters.
- **ROS**: Uses meters.
- **Conversion**:
    - Input object pose (ROS) is converted to Simox (mm) by multiplying position by 1000.0.
    - Output grasp poses (Simox) are converted to ROS (m) by dividing position by 1000.0.

### 4. RViz Configuration
- A default RViz configuration file is provided at `config/grasp_planner.rviz`.
- It is pre-configured to show:
    - Robot Model
    - Grasp Markers
    - TF Frames

## Usage

### Build
```bash
colcon build --packages-select grasp_planner_service
```

### Run Service
```bash
ros2 run grasp_planner_service grasp_planner_service_node
```

### Run Test Client
```bash
ros2 run grasp_planner_service test_grasp_planner
```

### Run RViz
```bash
rviz2 -d src/grasp_planner_service/config/grasp_planner.rviz
```

## Dependencies
- `visualization_msgs`
- `tf2_ros`
- `tf2_eigen`
