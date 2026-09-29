#!/usr/bin/env bash
# ==============================================================================
# install_simox.sh
# ==============================================================================
# Automated installer for the Simox C++ library (cram2 fork) and optional ROS 2
# grasp planning service packages.
#
# Suitable for local developer setups and GitHub Actions CI pipelines.
#
# Usage:
#   bash scripts/install_simox.sh [OPTIONS]
#
# Options:
#   --prefix <dir>       Installation prefix (default: /usr/local)
#   --simox-repo <url>   Simox git repository (default: https://github.com/cram2/Simox.git)
#   --simox-branch <br>  Simox git branch/tag (default: master)
#   --workdir <dir>      Working directory for build files (default: /tmp/simox_build)
#   --skip-deps          Skip apt-get dependency installation
#   --jobs <N>           Number of parallel build jobs (default: nproc)
#   --help               Show this help message
# ==============================================================================

set -euo pipefail

PREFIX="/usr/local"
SIMOX_REPO="https://github.com/cram2/Simox.git"
SIMOX_BRANCH="master"
WORKDIR="/tmp/simox_build"
SKIP_DEPS=false
JOBS="$(nproc)"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --prefix)
            PREFIX="$2"
            shift 2
            ;;
        --simox-repo)
            SIMOX_REPO="$2"
            shift 2
            ;;
        --simox-branch)
            SIMOX_BRANCH="$2"
            shift 2
            ;;
        --workdir)
            WORKDIR="$2"
            shift 2
            ;;
        --skip-deps)
            SKIP_DEPS=true
            shift 1
            ;;
        --jobs)
            JOBS="$2"
            shift 2
            ;;
        --help|-h)
            sed -ne '/^#/!q;s/^# //;2,$p' "$0"
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            exit 1
            ;;
    esac
done

SUDO=""
if [[ "$(id -u)" -ne 0 ]]; then
    if command -v sudo >/dev/null 2>&1; then
        SUDO="sudo"
    else
        echo "Warning: Not running as root and sudo not found. Installation to system dirs might fail." >&2
    fi
fi

# 1. Install APT build dependencies
if [[ "${SKIP_DEPS}" == false ]]; then
    echo "==> [1/4] Installing system build dependencies..."
    ${SUDO} apt-get update -qq
    ${SUDO} apt-get install -y -qq \
        build-essential \
        cmake \
        git \
        libboost-all-dev \
        libeigen3-dev \
        qtbase5-dev \
        libqt5opengl5-dev \
        libcoin-dev \
        libsoqt-dev-common \
        libnlopt-dev \
        liburdfdom-dev
fi

# 2. Clone Simox (cram2 fork)
echo "==> [2/4] Cloning Simox (${SIMOX_REPO}, branch: ${SIMOX_BRANCH})..."
mkdir -p "${WORKDIR}"
if [[ ! -d "${WORKDIR}/Simox/.git" ]]; then
    git clone --depth 1 --branch "${SIMOX_BRANCH}" "${SIMOX_REPO}" "${WORKDIR}/Simox"
else
    echo "    Using existing repository in ${WORKDIR}/Simox"
fi

# 3. Configure and compile Simox
echo "==> [3/4] Configuring and compiling Simox (jobs: ${JOBS})..."
cd "${WORKDIR}/Simox"
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${PREFIX}" \
    -DSimox_BUILD_EXAMPLES=OFF \
    -DSimox_BUILD_VirtualRobot=ON \
    -DSimox_BUILD_GraspStudio=ON \
    -DSimox_BUILD_SimDynamics=OFF \
    -DSimox_BUILD_Saba=OFF \
    -DBUILD_TESTING=OFF

cmake --build build -j"${JOBS}"

# 4. Install Simox
echo "==> [4/4] Installing Simox to ${PREFIX}..."
if [[ "${PREFIX}" == "/usr"* ]] || [[ "${PREFIX}" == "/etc"* ]]; then
    ${SUDO} cmake --install build
else
    cmake --install build
fi

echo "=============================================================================="
echo "✔ Simox installation complete!"
echo "  Installed to: ${PREFIX}"
echo "  CMake search path: ${PREFIX}/share/Simox/cmake"
echo "=============================================================================="
