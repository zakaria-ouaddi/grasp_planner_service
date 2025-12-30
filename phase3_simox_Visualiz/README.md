# Simox Native Viewer (Experimental)

**Status: DEPRECATED / EXPERIMENTAL**

This directory contains `simox_viewer.cpp`, a standalone C++ application designed to launch a native Qt/Coin3D window for viewing Simox robots and objects directly.

## Why is this here?
This was the initial attempt to visualize the grasp planning scene. It uses Simox's internal `SoQt` viewer.

## Why is it deprecated?
We encountered severe compatibility issues on modern Linux Desktop Environments (specifically Wayland and GLX), resulting in:
- Ghost windows (transparent/unresponsive).
- OpenGL context failures.
- X11 forwarding issues.

## Current Visualization Solution
**Do not use this viewer.**

Instead, use the **ROS2-RViz Bridge** implemented in `grasp_planner_service`.
1. The service converts Simox meshes to `visualization_msgs::Marker`.
2. You can view the entire scene reliably in standard **RViz2**.

See `../docs/PHASE_3_DOCUMENTATION.md` for details on the working visualization pipeline.
