# Phase 3: Usage Guide - How to Run the System

This guide provides step-by-step instructions to launch the full Grasp Planner system (Service + GUI + Visualization).

## 1. Setup Environment
Open 3 separate terminals. In *each* terminal, source your workspace:

```bash
cd ~/grasp_planner
source install/setup.bash
```

## 2. Launching the System

### Terminal 1: Support Services (RViz)
Launch RViz2 to see the visualization.

```bash
rviz2
```
**Configuration:**
1.  **Fixed Frame**: Set to `world`.
2.  **Add Topic**: Click "Add" -> By Topic -> `/robot_model` -> MarkerArray.
3.  **Add Topic**: Click "Add" -> By Topic -> `/grasp_markers` -> MarkerArray.
4.  *(Optional)*: Save this config as `grasp_config.rviz` for future use.

### Terminal 2: Grasp Planner Service
Start the C++ node. This loads Simox and waits for requests.

```bash
ros2 run grasp_planner_service grasp_planner_service_node
```
*You should see:* `[INFO] ... Grasp Planner Service (Phase 1-3) initialized`

### Terminal 3: GUI Client
Start the Python Interface.

```bash
python3 grasp_planner_gui/gui_client.py
```

## 3. Running a Grasp Plan

1.  **Configure GUI**:
    - **Robot XML**: Ensure it points to: `/grasp_planner/grasp_test_files/robots/ArmarIII/ArmarIII.xml`
    - **Object XML**: Ensure it points to: `/grasp_planner/grasp_test_files/objects/test_cube.xml`
    - **Kinematic Chain**: `TorsoRightArm`
    - **EEF Name**: `Hand R`
    - **Preshape**: `Power Preshape`

2.  **Set Position**:
    - **X**: `0.1`
    - **Y**: `0.6`
    - **Z**: `0.8` (Important: Must be reachable by the robot!)

3.  **Set Tuning**:
    - **Quality Threshold**: `0.01` (Low value ensures you see *something* even if grasps are weak).
    - **Grasps to Plan**: `50` (Higher number = slower but more variety).

4.  **Execute**:
    - Click the **"Plan Grasps"** button.

## 4. Expected Output

- **GUI**: Will show a popup: `SUCCESS: Found 50 valid grasps!`.
- **Terminal 2 (Service)**: Will scroll logs about "Generated grasps at origin" and "Moved object to pose".
- **RViz**:
    - **Robot**: Full ArmarIII robot appears in Grey.
    - **Object**: A Green Cube appears at table height (Z=0.8).
    - **Grasps**: Multiple Colored Arrows (Green/Red) appear sticking out of the cube.

## 5. Troubleshooting / Common Issues

- **"No valid grasps found"**:
    - Try lowering the `Quality Threshold` (e.g., to 0.001).
    - Ensure you are using `test_cube.xml` (75mm), NOT a large object like the 200mm cube.
    - Check terminal logs for "Low number of contacts".

- **"No reachable/collision-free grasps"**:
    - The object might be too far away. Try moving X/Y/Z closer to the robot (e.g., `x=0.2, y=0.4, z=1.0`).
    - The object might be inside the robot. Ensure Z is at least 0.8.

- **"Frame [world] does not exist"**:
    - Ensure `Fixed Frame` in RViz is typed exactly as `world`.
