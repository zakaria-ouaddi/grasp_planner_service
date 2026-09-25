#!/usr/bin/env bash
# launch_simox_service.sh
# =======================
# Launches the Simox grasp planner ROS 2 service with the correct library paths.
#
# Usage:
#   bash scripts/launch_simox_service.sh
#
# Requirements:
#   - ROS 2 Jazzy sourced (or run: source /opt/ros/jazzy/setup.bash)
#   - Grasp planner workspace built: colcon build --packages-select grasp_planner_service
#   - Simox built: cmake installed to /home/zakaria/local/simox-urdf or similar

set -eo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"

# Pre-initialize AMENT_TRACE_SETUP_FILES so ROS 2 setup.bash does not fail
# when the shell is started with set -u (unbound variable check).
export AMENT_TRACE_SETUP_FILES="${AMENT_TRACE_SETUP_FILES:-}"

# Source ROS 2 base (only if not already sourced)
if [[ -z "${ROS_DISTRO:-}" ]]; then
  source /opt/ros/jazzy/setup.bash
fi

# Source the workspace install (always, to pick up grasp_planner_msgs etc.)
source "$REPO_ROOT/install/setup.bash"

# Prefer simox-urdf which was built with SimoxURDF support
SIMOX_LIB_DIR=""
if [[ -d "/home/zakaria/local/simox-urdf/lib" ]]; then
    SIMOX_LIB_DIR="/home/zakaria/local/simox-urdf/lib"
elif [[ -f "$CMAKE_CACHE" ]]; then
    SIMOX_DIR=$(grep "^Simox_DIR:" "$CMAKE_CACHE" | cut -d= -f2)
    # Simox_DIR is .../share/Simox/cmake → go up 3 levels to find lib/
    if [[ -n "$SIMOX_DIR" ]]; then
        SIMOX_INSTALL=$(dirname "$(dirname "$(dirname "$SIMOX_DIR")")")
        if [[ -d "$SIMOX_INSTALL/lib" ]]; then
            SIMOX_LIB_DIR="$SIMOX_INSTALL/lib"
        fi
    fi
fi

# Fallback: known locations
if [[ -z "$SIMOX_LIB_DIR" ]]; then
    for candidate in \
        /home/zakaria/local/simox-urdf/lib \
        /home/zakaria/local/lib \
        /usr/local/lib
    do
        if ls "$candidate"/libVirtualRobot* &>/dev/null 2>&1; then
            SIMOX_LIB_DIR="$candidate"
            break
        fi
    done
fi

if [[ -z "$SIMOX_LIB_DIR" ]]; then
    echo "ERROR: Could not find Simox libraries (libVirtualRobot.so)."
    echo "Build Simox and set SIMOX_LIB_DIR manually:"
    echo "  SIMOX_LIB_DIR=/path/to/simox/lib bash scripts/launch_simox_service.sh"
    exit 1
fi

export LD_LIBRARY_PATH="$SIMOX_LIB_DIR:/home/zakaria/local/lib:${LD_LIBRARY_PATH:-}"
echo "[launch_simox_service] Using Simox libs: $SIMOX_LIB_DIR (and /home/zakaria/local/lib for rbdl)"
echo "[launch_simox_service] LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
echo "[launch_simox_service] Starting grasp_planner_service_node..."
echo ""

exec ros2 run grasp_planner_service grasp_planner_service_node "$@"
