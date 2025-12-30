# Phase 3: Debugging Log - Errors & Solutions

This document chronicles the specific technical challenges faced during Phase 3 and exactly how they were solved.

## 1. Simox Native Viewer Failure (Wayland/GLX)
*   **Error**: When launching the native Simox viewer, i got a "Ghost Window" (transparent/unresponsive) or X11 forwarding errors.
*   **Cause**: Incompatibility between Simox's older `SoQt` / Coin3D rendering and the modern Wayland desktop environment without proper XWayland configuration.
*   **Solution**: **Abandoned Native Viewer.** i implemented a "Bridge" function `createMeshMarker` that converts Simox geometry to ROS `visualization_msgs::Marker` messages, allowing us to use **RViz2** as the viewer.

## 2. RViz "Frame [world] does not exist"
*   **Error**: RViz showed no data and complained about missing transforms.
*   **Cause**: i was publishing Markers in the `world` frame, but no TF broadcaster was publishing the `world` -> `object_frame` or `world` -> `robot_base` transform.
*   **Solution**: Added a `tf2_ros::TransformBroadcaster` to `grasp_planner_service.cpp` to publish a static identity transform for the world frame.

## 3. Robot Base "Buried" in Floor
*   **Error**: The `ArmarIII` robot appeared with its waist at Z=0, meaning the legs were clipped through the floor.
*   **Cause**: i was using a standalone `RightArm.xml` or incorrect root node scaling.
*   **Solution**: Switched to the Full `ArmarIII.xml` robot model which has a proper `Platform` root node.I also initially tried manually applying a Z=1.1m offset, but reverted this in favor of using the correct robot model physics.

## 4. "Low Number of Contacts" (Geometric Issue)
*   **Error**: Simox Log: `ignoring grasp hypothesis, low number of contacts`.
*   **Cause**: Using the `ArmarIII` hand (human-sized) to grasp a **200mm Cube** was physically impossible (the hand couldn't wrap around it).
*   **Solution**: Resized the test object `test_cube.iv` to **75mm**, which is the ideal "Goldilocks" size for a human-hand power grasp.

## 5. "No Valid Grasps" (The Critical Logic Bug)
*   **Error**: Even with the 75mm cube, the planner returned 0 grasps.
*   **Cause**: I was setting `this->object->setGlobalPose(user_pose)` **BEFORE** calling `planner->plan()`.
*   **Technical Detail**: The `ApproachMovementSurfaceNormal` algorithms calculate approach vectors based on the object's local frame. By moving the object to (e.g.) `Z=0.8` before planning, the calculated vectors became invalid/misaligned relative to the object's surface normals in the planner's internal reference frame.
*   **Solution**: **Defer the Move.** I modified the code to:
    1.  Keep Object at (0,0,0).
    2.  Check for Grasps.
    3.  *Then* move Object to (0,0,0.8).

## 6. Reused End-Effector State Corruption
*   **Error**: The planner behavior was inconsistent across multiple runs.
*   **Cause**: I was passing the raw `EndEffectorPtr` to the planner. The planner moves the fingers during testing. Without resetting, subsequent grasp tests started with "closed" fingers.
*   **Solution**: Added `approach->getEEFRobotClone()` to ensure every grasp test starts with a fresh hand state.

## 7. Visualization Mismatch ("Floating Arrows")
*   **Error**: After fixing the logic, I saw the object at Z=0.8, but the Grasp Arrows were at Z=0 (or vice versa).
*   **Cause**: I was publishing the object marker *before* moving it, or publishing grasp markers based on the old pose.
*   **Solution**: Added a call to `publish_object_marker(eigen_object_pose)` immediately **AFTER** the object setGlobalPose call, ensuring the visual marker matches the physical collision model used for Phase 2 checks.
