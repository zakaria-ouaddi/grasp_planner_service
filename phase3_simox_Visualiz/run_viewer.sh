#!/bin/bash

# 1. Bypass the specific known Coin3D/Mesa crash
export COIN_GL_NO_CURRENT_CONTEXT_CHECK=1

# 4. Path to your binary
# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
BINARY_PATH="$SCRIPT_DIR/build/simox_viewer"

echo "Starting Simox Viewer..."
$BINARY_PATH