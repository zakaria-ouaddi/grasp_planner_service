# Grasp Planner GUI - User Guide

This graphical interface allows you to interactively test the **Grasp Planner Service** without writing C++ code. You can load different objects, tweak planner settings, adjust object 6D pose, and visualize the results instantly.

## 1. How to Run

### Prerequisites
*   Ensure the **Grasp Planner Service** is running in a separate terminal:
    ```bash
    source install/setup.bash
    ros2 run grasp_planner_service grasp_planner_service_node
    ```

### Launch the GUI
Open a **new terminal** and run:
```bash
source install/setup.bash
python3 grasp_planner_gui/gui_client.py
```

---

## 2. Configuration Parameters

Here is a detailed explanation of every input field, along with the **Recommended Values** for the `ArmarIII` robot.

### A. Model Files
*   **Robot XML**: Path to the robot definition file.
    *   *Default*: `.../grasp_test_files/robots/ArmarIII/ArmarIII.xml`
*   **Object XML**: Path to the object you want to grasp.
    *   *Default*: `.../grasp_test_files/objects/test_cube.xml`
    *   *Tip*: You can click `...` to browse for other objects.

### B. Planner Configuration

| Parameter | Recommended Value | Description |
| :--- | :--- | :--- |
| **End Effector** | `Hand R` | The name of the End Effector (EEE) defined in the robot XML. <br>**Must match exactly.** |
| **Kinematic Chain** | `TorsoRightArm` | The kinematic chain (set of joints) connecting the robot base to the hand. used for inverse kinematics (Reachability checks). |
| **Preshape Name** | `Power Preshape` | **Power Preshape**: Closes all fingers together. <br>Use for **Large/Cylindrical** objects (Bottles, Boxes, Cups). <br><br> **Precision Preshape**: Pinches with fingertips.<br>Use for **Small/Thin** objects (Pens, Nails, Cutlery). |
| **Quality Threshold** | `0.01` | The minimum "Grasp Quality" score (0.0 - 1.0) to accept.<br>• **0.01**: Accepts weak grasps (easier to find).<br>• **0.05**: Robust grasps (standard).<br>• **0.10+**: Very strong grasps (harder to find). |
| **Timeout (ms)** | `30000` | Maximum time to search for grasps (in milliseconds). <br>30000 (30s) is recommended as 3D collision checking is CPU intensive. |
| **Num Grasps** | `50` | The service will stop once it finds this many valid grasps. |

### C. Object Pose (6D Control)
Fully control where the object is located in the 3D world relative to the robot base.

*   **Position (X / Y / Z)**: in meters.
    *   *Recommended*: `0.1, 0.6, 0.8` (A reachable point on a virtual table).
*   **Orientation (Roll / Pitch / Yaw)**: in degrees.
    *   *Recommended*: `0, 0, 0` (Upright).
    *   The GUI automatically converts these Euler angles to the Quaternion required by the ROS service.

---

## 3. Interpreting Results

Click **[Plan Grasps]** to send the request.

*   **SUCCESS**: 
    *   *Message*: `Found X valid grasps!`
    *   *Output*: Shows the **Best Quality** score and the **Position** of the best grasp.
    *   *Action*: The service has successfully calculated a stable grasp.

*   **FAILURE**:
    *   *Message*: `No valid grasps found`
    *   *Reasons*:
        1.  **Object out of reach** (Check Pose X/Y/Z).
        2.  **Object inside Robot** (Check Z > 0.0!).
        3.  **Scale Issue** (Ensure object is reasonable size, e.g. 75mm).
        4.  **Collision** (Object might be clipping through the robot).
