# Grasp Planner Service: Phases 1 & 2 Documentation

This document explains the implementation of Phase 1 (Basic Grasp Generation) and Phase 2 (Reachability & Collision Avoidance) of the Grasp Planner Service, and provides instructions on how to test the system with different robots and objects.

## Phase 1: Basic Grasp Generation

The goal of Phase 1 is to generate a set of candidate grasps for a given object using a specified robot end-effector, without considering the robot's arm kinematics or environment collisions.

### Implementation Details
- **Library**: Uses `Simox` (specifically `GraspStudio` and `VirtualRobot`).
- **Process**:
    1.  **Load Models**: Loads the Robot XML and Object XML files specified in the request.
    2.  **Set Object Pose**: Updates the object's global pose based on the request.
    3.  **Quality Measure**: Initializes `GraspStudio::GraspQualityMeasureWrenchSpace` to evaluate grasp quality based on force closure properties.
    4.  **Approach Movement**: Initializes `GraspStudio::ApproachMovementSurfaceNormal` to generate approach directions based on the object's surface normals.
    5.  **Planning**: Uses `GraspStudio::GenericGraspPlanner` to iteratively generate grasps.
        - It attempts to close the hand (End Effector) around the object.
        - It checks if the grasp satisfies "Force Closure" (stable grasp).
        - It calculates a quality score (0.0 to 1.0).

## Phase 2: Reachability & Collision Avoidance

The goal of Phase 2 is to filter the candidate grasps generated in Phase 1 to ensure they are valid for the specific robot arm configuration.

### Implementation Details
- **Library**: Uses `VirtualRobot` (part of Simox).
- **Process**:
    1.  **IK Solver Setup**: If a `kinematic_chain_name` is provided (e.g., "RightArm"), it creates a `VirtualRobot::DifferentialIK` solver for that chain.
    2.  **Collision Manager Setup**: Creates a `VirtualRobot::CDManager` and adds the robot's nodes (links) to it to check for self-collisions.
    3.  **Filtering Loop**: Iterates through every grasp found in Phase 1:
        - **Reachability Check**:
            - Calculates the global pose of the TCP (Tool Center Point) for the grasp.
            - Uses the IK solver (`solveIK()`) to check if the robot arm can physically reach this pose.
            - If unreachable, the grasp is discarded.
        - **Collision Check**:
            - Checks if the robot is in a valid configuration (no self-collisions) at the solved IK pose.
            - If a collision is detected, the grasp is discarded.
    4.  **Ranking**: The remaining valid grasps are sorted by their quality score (highest first).
    5.  **Response**: The service returns the list of valid, reachable, collision-free grasp poses.

## How to Test with Different Robots and Objects

The system is designed to be flexible. You can test different scenarios by changing the parameters passed to the test node.

### Prerequisites
1.  **Build the workspace**:
    ```bash
    colcon build --symlink-install
    source install/setup.bash
    ```
2.  **Run the Service**:
    In one terminal:
    ```bash
    ros2 run grasp_planner_service grasp_planner_service_node
    ```

### Running the Test Client
In a second terminal, run the test client. You can use the default values (ArmarIII robot and a plate object) or override them.

#### 1. Default Test (ArmarIII + Plate)
```bash
ros2 run grasp_planner_service test_grasp_planner
```

#### 2. Testing with Custom Parameters
You can override any of the following parameters:
- `robot_model_path`: Path to the robot XML file.
- `object_model_path`: Path to the object XML file.
- `end_effector_name`: Name of the end effector in the robot XML (e.g., "Hand R", "TCP L").
- `kinematic_chain_name`: Name of the kinematic chain (e.g., "RightArm", "LeftArm").
- `preshape_name`: (Optional) Name of a preshape to apply (e.g., "Open", "Pinch").
- `object_pose_x`, `object_pose_y`, `object_pose_z`: Position of the object in the world.

**Example: Testing with a different object (e.g., a mug)**
```bash
ros2 run grasp_planner_service test_grasp_planner --ros-args \
    -p object_model_path:=/path/to/mug.xml \
    -p object_pose_z:=300.0
```

**Example: Testing with a different Robot (e.g., Armar4)**
```bash
ros2 run grasp_planner_service test_grasp_planner --ros-args \
    -p robot_model_path:=/path/to/Armar4.xml \
    -p end_effector_name:="Hand R" \
    -p kinematic_chain_name:="RightArm"
```

### Troubleshooting
- **"End effector not found"**: Check the robot XML file specifically for the `<EndEffector name="...">` tag and ensure your parameter matches exactly.
- **"Kinematic chain not found"**: Check the robot XML for `<RobotNodeSet name="...">` that defines the chain.
- **"No valid grasps found"**:
    - The object might be too far away (Reachability failed). Try moving the object closer (change `object_pose_x/y/z`).
    - The object might be too large for the hand.
    - The quality threshold might be too high (default is 0.01).
