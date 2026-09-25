# How Simox "Closes" the Hand: A Technical Deep Dive

This document explains the internal mechanism Simox uses to simulate a robotic hand grasping an object. Contrary to physics-based simulators (like Gazebo or MuJoCo) that use forces and friction, Simox uses a geometric **Constraint-Based Approach** relying heavily on Collision Detection.

## 1. The Core Concept: Kinematic Closure
Simox does not "simulate" muscles or motors. Instead, it performs a **Kinematic Closure**:
*   It iteratively moves finger joints.
*   It stops movement upon collision.
*   It calculates resultant forces based on geometry.

## 2. The Step-by-Step Process

### Phase 1: Approach & Alignment
Before closing fingers, the planner positions the hand:
1.  **Sampler**: Selects a random point on the object's surface.
2.  **Alignment**: Aligns the **End Effector's Approach Direction** (usually Z-axis) with the negative surface normal of that point.
3.  **Approach**: Moves the hand along this vector until a predefined standoff distance is reached (virtual "palm touch").

### Phase 2: The "Closing" Loop (`closeActors`)
This is the critical "gripping" phase. It happens inside `VirtualRobot::EndEffector::closeActors()`:

1.  **Initialization**: Simox identifies all **Actor Nodes** (fingers) defined in the robot's `EndEffector` configuration.
2.  **Iteration Loop**:
    *   **Step**: It increments the joint values of all fingers by a small delta (e.g., 0.05 radians).
    *   **Updates**: It updates the Forward Kinematics (FK) to reflect the new finger positions.
    *   **Collision Check**: It runs a **Collision Detection (CD)** query between:
        *   Each **Finger Link Collaboration Model**.
        *   The **Object's Collision Model**.
3.  **Stop Condition**:
    *   **IF Collision**: The specific finger causing collision **STOPS** moving. It is marked as "In Contact".
    *   **IF Joint Limit**: If a finger extends fully without hitting anything, it stops at its limit (a "miss").
4.  **Completion**: The loop continues until **ALL** fingers have stopped.

### Phase 3: Contact Analysis & Quality
Once the hand is static (closed):
1.  **Contact Point Extraction**: Simox retrieves the exact 3D coordinates where the finger meshes intersect the object mesh.
2.  **Virtual Contacts**: It places "Virtual Contacts" at these points.
3.  **Friction Cone Generation**: At each contact point, it generates a Friction Cone (based on a configured friction coefficient, typ. 0.5).
4.  **Grasp Wrench Space (GWS)**: It calculates the 6D Wrench Space (Force + Torque) spanned by these friction cones.
5.  **Quality Score**:
    *   **Volume**: The quality score is often the volume of this wrench space.
    *   **Epsilon**: Or the radius of the largest ball inscribed in the wrench space (meaning the minimum disturbance force needed to break the grasp).

## Key Takeaways for Debugging
*   **Collision Models Matter**: If your collision model is too coarse (a simple box), the fingers might stop "in mid-air" visually.
*   **Step Size**: If the step size is too large, fingers might "penetrate" the object deeply before detection, leading to unrealistic contact forces.
*   **No Physics**: This grasp is valid *geometrically*. It does not guarantee the object won't slip under dynamic motion (shaking) unless the GWS score is high.
