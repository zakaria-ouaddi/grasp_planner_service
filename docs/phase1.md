# Phase 1: Core Integration & API Development

## Overview
The goal of Phase 1 was to establish the basic infrastructure for the Grasp Planner Service. We focused on creating a ROS 2 service that could interface with the Simox/GraspStudio libraries to generate grasp candidates for a given object and robot.

## What We Did

### 1. Service Definition (`PlanGrasp.srv`)
We defined the `PlanGrasp` service in the `grasp_planner_msgs` package.
- **Request**:
    - `robot_model_path`: Path to the robot XML file.
    - `object_model_path`: Path to the object XML file.
    - `end_effector_name`: Name of the end effector (EEF) to use.
    - `preshape_name`: Name of the preshape to apply before grasping.
    - `quality_threshold`: Minimum quality score for a grasp to be accepted.
    - `timeout_ms`: Maximum time allowed for planning.
- **Response**:
    - `success`: Boolean indicating if grasps were found.
    - `grasp_poses`: List of generated grasp poses (initially just a flat list or single pose).

### 2. Service Implementation (`grasp_planner_service.cpp`)
We implemented the core node `grasp_planner_service`.
- **Simox Integration**: Used `VirtualRobot` to load robot and object models from the file system.
- **Grasp Planner**: Initialized `GraspStudio::GenericGraspPlanner` to generate grasp candidates.
- **Quality Measure**: Used `GraspStudio::GraspQualityMeasureWrenchSpace` to evaluate grasps based on force closure.
- **Approach Movement**: Configured `GraspStudio::ApproachMovementSurfaceNormal` to simulate the gripper approaching the object surface.

### 3. Test Client (`test_grasp_planner.cpp`)
We created a simple test node to verify the service.
- It sends a request with hardcoded paths to a test robot (e.g., `Tracy`) and a test object.
- It prints whether the service call was successful.

## Challenges & Solutions

### Missing Dependencies
- **Issue**: The compiler could not find `VirtualRobot` or `GraspStudio` headers.
- **Solution**: We updated `CMakeLists.txt` to properly find and link these Simox packages using `find_package(Simox REQUIRED)` and `target_link_libraries`.

### Header File Errors
- **Issue**: "File not found" errors for standard ROS messages like `geometry_msgs/msg/point.hpp`.
- **Solution**: We ensured `geometry_msgs` and `rclcpp` were listed in `package.xml` and `CMakeLists.txt`.

### Path Resolution
- **Issue**: The service required absolute paths to XML files, which could vary between users.
- **Solution**: For Phase 1, we used hardcoded paths or expected the user to provide valid absolute paths. (Later improved in Phase 2/3 with parameters).

## How to Run Phase 1

### 1. Build the Package
```bash
colcon build --packages-select grasp_planner_msgs grasp_planner_service
source install/setup.bash
```

### 2. Run the Service
```bash
ros2 run grasp_planner_service grasp_planner_service
```

### 3. Run the Test Client
Open a new terminal, source the workspace, and run:
```bash
ros2 run grasp_planner_service test_grasp_planner
```
*Note: Ensure the test files (robot and object XMLs) exist at the paths specified in the test client code.*
