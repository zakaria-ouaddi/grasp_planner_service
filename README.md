# ROS2 Simox Grasp Planner

## Overview
**Simox Grasp Planner** is a powerful ROS2-based manipulation framework that bridges the gap between high-level task planning and low-level grasp synthesis. Built on top of the robust [Simox Robotics Library](https://gitlab.com/Simox/simox), this project provides a unified service to generate, filter, and visualize stable grasps for humanoid robots (e.g., ArmarIII).

It solves the "Black Box" problem of grasping by providing a transparent, debuggable pipeline:
1.  **Generate**: Synthesizes grasps using Simox's `GenericGraspPlanner`.
2.  **Filter**: Validates grasps against Kinematic Reachability and Collision constraints.
3.  **Visualize**: Bridges internal physics states to standard **RViz2** markers.

## ✨ Key Features
*   **ROS2 Service Interface**: Standard `PlanGrasp.srv` for easy integration with other nodes.
*   **Physics-Based Planning**: Uses `GraspStudio` for force-closure and quality metrics.
*   **Reachability Awareness**: Integrated `DifferentialIK` solver rejects unreachable grasps.
*   **Visualization Bridge**: See internal Simox meshes and grasp vectors directly in RViz.
*   **Interactive Python GUI**: No coding needed to test—tweak parameters and see results instantly.
*   **Persistent Logging**: Automated CSV logging for offline analysis.

## 📦 Dependencies
*   **ROS2** (Humble/Iron)
*   **[Simox](https://gitlab.com/Simox/simox)**: The core robotics/grasping library.
*   **Python 3** + `tkinter` (for the GUI client).

## 🚀 Quick Start

### 1. Build
```bash
cd ~/grasp_planner
colcon build --packages-select grasp_planner_service
source install/setup.bash
```

### 2. Run the System
We provide a separate GUI for easy testing.

**Terminal 1: The Service**
```bash
ros2 run grasp_planner_service grasp_planner_service_node
```

**Terminal 2: The GUI**
```bash
python3 grasp_planner_gui/gui_client.py
```

**Terminal 3: Visualization**
```bash
rviz2
# Add MarkerArray topics: /robot_model and /grasp_markers
```

## 📚 Documentation
*   **[Usage Guide](docs/PHASE_3_USAGE_GUIDE.md)**: Detailed step-by-step instructions.
*   **[Architecture & Debugging](docs/PHASE_3_DOCUMENTATION.md)**: Deep dive into the implementation and critical debugging logs.
*   **[GUI Manual](grasp_planner_gui/README.md)**: Explanation of all configuration parameters.

## 🔗 Credits & References
*   **Simox Library**: [https://gitlab.com/Simox/simox](https://gitlab.com/Simox/simox)
*   **VirtualRobot**: The underlying kinematic engine.
*   **GraspStudio**: The grasp generation algorithms.
