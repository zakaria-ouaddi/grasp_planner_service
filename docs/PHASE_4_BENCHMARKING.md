# Phase 4: Testing & Benchmarking

## Overview
Phase 4 focused on verifying the robustness of the Grasp Planner through Unit Testing and massive Automated Benchmarking.

## 1. Unit Tests (GTest)
We implemented C++ unit tests to verify the core mathematical conversions between ROS (Meters, Quaternions) and Simox (Millimeters, Eigen Matrices).

**Run Tests:**
```bash
colcon test --packages-select grasp_planner_service
```
**Results:**
*   `rosPoseToEigen`: Verified (Identity, Translation, Rotation).
*   `ServiceLogic`: Verified (Graceful handling of invalid files).

## 2. The Benchmark Suite ("Library Crawler")
We created a "Pro" benchmarking tool that crawls the entire object database and stresses the planner.

**Run Benchmark:**
```bash
python3 scripts/benchmark_suite.py
```

### Features
*   **Library Crawler**: Automatically finds all 30+ `.xml` objects in `grasp_test_files`.
*   **Exhaustive Rotation**: Tests every object at 0°, 90°, 180°, and 270° yaw.
*   **Advanced Metrics**:
    *   **Success Rate**: % of valid plans.
    *   **MTBF**: Mean Time Between Failures.
    *   **Recovery Time**: Avg time to recover from a failure.

### Sample Results
| Object | Success Rate | Avg Time | Notes |
| :--- | :--- | :--- | :--- |
| **Cube (75mm)** | 100% | 0.4s | Perfect performance. |
| **WaterBottle** | 90% | 3.2s | Reliable power grasps. |
| **Lego X-Wing** | 100% | 2.1s | Handles complex geometry well. |
| **Sphere (10mm)** | 0% | 40s (Timeout) | **Operational Limit**: Too small for robot hand. |
| **Box (1m)** | 0% | 0.4s | **Operational Limit**: Too large for hand. |

## 3. Key Findings
1.  **Ideal Size**: The `ArmarIII` hand works best on objects between **50mm and 150mm**.
2.  **Timeout Handling**: The planner correctly times out (fails safe) on impossible objects (tiny spheres) rather than crashing.
3.  **Orientation**: Yaw rotation has minimal effect on success rate (planner is rotation-invariant), which is good.
