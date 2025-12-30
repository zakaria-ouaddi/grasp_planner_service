#!/bin/bash

# 1. Bypass the specific known Coin3D/Mesa crash
export COIN_GL_NO_CURRENT_CONTEXT_CHECK=1

# 4. Path to your binary
BINARY_PATH="/home/zakaria/grasp_planner/phase3_simox_Visualiz/build/simox_viewer"

echo "Starting Simox Viewer..."
$BINARY_PATH