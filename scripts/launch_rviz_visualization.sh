#!/usr/bin/env bash
# launch_rviz_visualization.sh
# =============================
# Starts everything needed to visualise the Simox grasp planner in RViz2:
#
#   1. robot_state_publisher  → publishes the PR2 TF tree + /robot_description
#   2. joint_state_publisher  → keeps all joints at zero (so the robot renders)
#   3. static_transform_publisher → world frame (parent of everything)
#   4. rviz2                  → opens with pre-configured grasp_planner.rviz
#
# Run BEFORE (or alongside) the Simox service and the demo.
# Once the service is called, grasp arrows will appear in RViz automatically.
#
# Usage:
#   bash scripts/launch_rviz_visualization.sh

set -eo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
RVIZ_CONFIG="$REPO_ROOT/grasp_test_files/rviz/grasp_planner.rviz"

# Silence ROS 2 unbound variable issue
export AMENT_TRACE_SETUP_FILES="${AMENT_TRACE_SETUP_FILES:-}"

if [[ -z "${ROS_DISTRO:-}" ]]; then
  source /opt/ros/jazzy/setup.bash
fi
source "$REPO_ROOT/install/setup.bash"

echo "[rviz_viz] Starting RViz2 with config: $RVIZ_CONFIG"
echo "[rviz_viz] Fixed frame: 'world'"
echo "[rviz_viz] Display: MarkerArray on /grasp_markers"
echo ""

exec rviz2 -d "$RVIZ_CONFIG"

