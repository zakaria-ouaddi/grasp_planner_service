#!/usr/bin/env python3
"""
convert_to_simox_ready.py
=========================
Converts any URDF robot or object file into a Simox-ready format using
Multiverse-Parser as the preprocessing engine.

Workflow:
  1. URDF (with package:// or file:// mesh refs) → Multiverse-Parser → Clean URDF
     (all meshes resolved to absolute paths, converted to STL if needed)
  2. Meshes copied to: grasp_test_files/resources/meshes/<name>/
  3. Clean URDF saved to: grasp_test_files/resources/robots/<name>_clean.urdf
  4. Simox XML wrapper auto-generated: grasp_test_files/resources/robots/<name>.xml

Usage:
  python3 scripts/convert_to_simox_ready.py \\
      --input grasp_test_files/iai_pr2/iai_pr2_description/robots/pr2.urdf \\
      --name pr2 \\
      --ros-package grasp_test_files/iai_pr2/iai_pr2_description

The generated <name>.xml is a template — you MUST edit it to fill in the
correct EEF names, kinematic chain nodes, and preshape values for your robot.
"""

import argparse
import os
import sys
import shutil
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------
SCRIPT_DIR = Path(__file__).parent.resolve()
PROJECT_ROOT = SCRIPT_DIR.parent
RESOURCES_DIR = PROJECT_ROOT / "grasp_test_files" / "resources"
ROBOTS_DIR = RESOURCES_DIR / "robots"
MESHES_DIR = RESOURCES_DIR / "meshes"
MULTIVERSE_PARSER_DIR = PROJECT_ROOT / "Multiverse-Parser"
MULTIVERSE_PARSER_SCRIPT = MULTIVERSE_PARSER_DIR / "scripts" / "multiverse_parser"


def check_prerequisites():
    """Verify Multiverse-Parser is installed and Blender is ready."""
    if not MULTIVERSE_PARSER_DIR.exists():
        print(f"[ERROR] Multiverse-Parser not found at {MULTIVERSE_PARSER_DIR}")
        print("  Run: git clone https://github.com/Multiverse-Framework/Multiverse-Parser "
              "--depth 1 grasp_planner/Multiverse-Parser")
        sys.exit(1)

    blender_path = MULTIVERSE_PARSER_DIR / "ext" / "blender" / "blender"
    if not blender_path.exists():
        print("[ERROR] Blender not found. Run setup.sh first:")
        print(f"  cd {MULTIVERSE_PARSER_DIR} && bash setup.sh")
        sys.exit(1)

    if not MULTIVERSE_PARSER_SCRIPT.exists():
        print(f"[ERROR] multiverse_parser script not found at {MULTIVERSE_PARSER_SCRIPT}")
        sys.exit(1)

    print("[OK] Multiverse-Parser prerequisites satisfied.")


def resolve_package_uri_env(ros_package_path: str | None):
    """
    Set ROS_PACKAGE_PATH so rospkg can resolve package:// URIs.
    If a custom ros_package_path is provided, prepend it.
    """
    env = os.environ.copy()
    if ros_package_path:
        ros_package_path = str(Path(ros_package_path).resolve())
        existing = env.get("ROS_PACKAGE_PATH", "")
        env["ROS_PACKAGE_PATH"] = f"{ros_package_path}:{existing}" if existing else ros_package_path
        print(f"[INFO] ROS_PACKAGE_PATH set to: {env['ROS_PACKAGE_PATH']}")
    return env


def run_multiverse_parser(input_urdf: Path, output_urdf: Path, env: dict):
    """
    Run Multiverse-Parser to convert input URDF → clean output URDF.
    All package:// mesh URIs are resolved and meshes copied/converted to STL.
    """
    print(f"\n[STEP] Running Multiverse-Parser:")
    print(f"  Input : {input_urdf}")
    print(f"  Output: {output_urdf}")

    output_urdf.parent.mkdir(parents=True, exist_ok=True)

    cmd = [
        str(MULTIVERSE_PARSER_SCRIPT),
        "--input", str(input_urdf),
        "--output", str(output_urdf),
        "--no-physics",  # We only need geometry for Simox; skip physics inertias
    ]

    result = subprocess.run(cmd, env=env, capture_output=False, text=True)
    if result.returncode != 0:
        print(f"[ERROR] Multiverse-Parser failed with exit code {result.returncode}")
        sys.exit(1)

    if not output_urdf.exists():
        print(f"[ERROR] Output URDF not created at {output_urdf}")
        sys.exit(1)

    print(f"[OK] Clean URDF generated: {output_urdf}")
    return output_urdf


def collect_mesh_paths(clean_urdf: Path) -> list[str]:
    """Parse the clean URDF and return all mesh file references."""
    tree = ET.parse(clean_urdf)
    root = tree.getroot()
    meshes = []
    for mesh_elem in root.findall(".//mesh"):
        filename = mesh_elem.get("filename", "")
        if filename:
            meshes.append(filename)
    return meshes


def copy_meshes(clean_urdf: Path, robot_name: str) -> Path:
    """
    Copy all mesh files referenced in the clean URDF into
    grasp_test_files/resources/meshes/<robot_name>/
    and rewrite the URDF mesh paths to be relative.

    Returns the mesh output directory.
    """
    mesh_out_dir = MESHES_DIR / robot_name
    mesh_out_dir.mkdir(parents=True, exist_ok=True)

    tree = ET.parse(clean_urdf)
    root = tree.getroot()
    urdf_dir = clean_urdf.parent

    changed = 0
    for mesh_elem in root.findall(".//mesh"):
        filename = mesh_elem.get("filename", "")
        if not filename:
            continue

        # Resolve absolute path
        if os.path.isabs(filename):
            src = Path(filename)
        else:
            src = (urdf_dir / filename).resolve()

        if not src.exists():
            print(f"  [WARN] Mesh not found, skipping: {src}")
            continue

        dst = mesh_out_dir / src.name
        shutil.copy2(src, dst)

        # Rewrite path to relative (from the URDF file location)
        rel_path = os.path.relpath(dst, clean_urdf.parent)
        mesh_elem.set("filename", rel_path)
        changed += 1

    if changed > 0:
        tree.write(clean_urdf, xml_declaration=True, encoding="unicode")
        print(f"[OK] Copied {changed} mesh files → {mesh_out_dir}")
        print(f"[OK] Updated mesh paths in URDF to relative paths.")

    return mesh_out_dir


def extract_urdf_info(urdf_path: Path) -> dict:
    """
    Extract useful info from the URDF for generating the Simox XML wrapper:
    - robot name
    - root link
    - list of link names
    """
    tree = ET.parse(urdf_path)
    root = tree.getroot()

    robot_name = root.get("name", "robot")
    links = [link.get("name") for link in root.findall("link")]
    joints = root.findall("joint")

    # Find root link (has no parent joint)
    child_links = set()
    for joint in joints:
        child = joint.find("child")
        if child is not None:
            child_links.add(child.get("link", ""))
    root_links = [l for l in links if l not in child_links]
    root_link = root_links[0] if root_links else (links[0] if links else "base_link")

    return {"robot_name": robot_name, "root_link": root_link, "links": links}


def generate_simox_wrapper(robot_name: str, clean_urdf_filename: str,
                            urdf_info: dict, output_path: Path):
    """
    Auto-generate a Simox XML wrapper that:
    - Loads the clean URDF via <ChildFromRobot>
    - Has placeholder <RobotNodeSet> and <EndEffector> sections

    The user MUST fill in the EEF base/tcp node names, chain nodes, and preshape values.
    """
    robot_display_name = urdf_info["robot_name"]
    root_link = urdf_info["root_link"]

    xml_content = f"""<?xml version="1.0" encoding="UTF-8" ?>
<!--
  Simox XML wrapper for {robot_display_name} (auto-generated by convert_to_simox_ready.py)

  TODO: Edit this file to fill in correct values:
    1. Replace placeholder EEF base/tcp link names with real ones from your URDF
    2. Add the correct links to RobotNodeSet <Node> lists
    3. Set correct preshape joint values
-->
<Robot Type="{robot_display_name}" StandardName="{robot_name}" RootNode="SimoxURDFLoader">
    <RobotNode name="SimoxURDFLoader">
        <ChildFromRobot>
            <File importEEF="true">{clean_urdf_filename}</File>
        </ChildFromRobot>
    </RobotNode>

    <!--
        === KINEMATIC CHAINS ===
        Define RobotNodeSet for each arm / kinematic chain.
        kinematicRoot: the shoulder/base link of the chain
        tcp: the tool-center-point link (end of chain)
        Then list all intermediate links with <Node> tags.

        EXAMPLE (replace with real link names from your URDF):
    -->
    <RobotNodeSet name="RightArm" kinematicRoot="{root_link}" tcp="TODO_TCP_LINK">
        <!-- <Node name="TODO_LINK_1"/> -->
        <!-- <Node name="TODO_LINK_2"/> -->
        <!-- ... -->
        <!-- <Node name="TODO_TCP_LINK"/> -->
    </RobotNodeSet>

    <!--
        === END EFFECTOR ===
        Define EndEffector for each hand/gripper.
        base: palm/base link of the EEF
        tcp:  tool-center-point
        gcp:  grasp-center-point (usually same as tcp)

        EXAMPLE:
    -->
    <EndEffector name="RightHand" base="TODO_PALM_LINK" tcp="TODO_TCP_LINK" gcp="TODO_TCP_LINK">

        <!-- Open preshape: fingers fully open -->
        <Preshape name="Open">
            <!-- <Node name="TODO_FINGER_JOINT" unit="radian" value="0.0"/> -->
        </Preshape>

        <!-- Power grasp: wide grip for large objects -->
        <Preshape name="Power Preshape">
            <!-- <Node name="TODO_FINGER_JOINT" unit="radian" value="0.5"/> -->
        </Preshape>

        <!-- Precision grasp: tight grip for small objects -->
        <Preshape name="Precision Preshape">
            <!-- <Node name="TODO_FINGER_JOINT" unit="radian" value="0.1"/> -->
        </Preshape>

        <!-- Static links (palm, non-moving parts) -->
        <Static>
            <!-- <Node name="TODO_PALM_LINK"/> -->
        </Static>

        <!-- Finger actors (moving finger links) -->
        <!-- <Actor name="Finger1">
            <Node name="TODO_FINGER_LINK"/>
        </Actor> -->

    </EndEffector>

</Robot>
"""

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, "w") as f:
        f.write(xml_content)

    print(f"[OK] Simox XML wrapper generated: {output_path}")
    print()
    print("  *** ACTION REQUIRED ***")
    print(f"  Edit {output_path} and fill in:")
    print("    1. RobotNodeSet kinematicRoot, tcp, and <Node> link names")
    print("    2. EndEffector base, tcp, and preshape joint values")
    print("    3. Static and Actor sections for finger links")


def main():
    parser = argparse.ArgumentParser(
        description="Convert a URDF robot/object to Simox-ready format using Multiverse-Parser."
    )
    parser.add_argument("--input", required=True,
                        help="Path to the input URDF file")
    parser.add_argument("--name", required=True,
                        help="Short name for the robot/object (e.g. 'pr2', 'franka')")
    parser.add_argument("--ros-package", default=None,
                        help="Path to the ROS package directory containing the URDF "
                             "(parent of package.xml). Used to resolve package:// URIs. "
                             "If omitted, relies on ROS_PACKAGE_PATH env var or rospkg.")
    parser.add_argument("--skip-parser", action="store_true",
                        help="Skip running Multiverse-Parser (use if already converted). "
                             "Will reuse existing <name>_clean.urdf if present.")

    args = parser.parse_args()

    input_urdf = Path(args.input).resolve()
    if not input_urdf.exists():
        print(f"[ERROR] Input URDF not found: {input_urdf}")
        sys.exit(1)

    robot_name = args.name
    clean_urdf = ROBOTS_DIR / f"{robot_name}_clean.urdf"
    simox_wrapper = ROBOTS_DIR / f"{robot_name}.xml"

    print(f"\n=== Simox-Ready Converter: {robot_name} ===\n")
    print(f"  Input URDF   : {input_urdf}")
    print(f"  Clean URDF   : {clean_urdf}")
    print(f"  Simox wrapper: {simox_wrapper}")
    print(f"  Mesh output  : {MESHES_DIR / robot_name}")
    print()

    # Phase 1: Prerequisites
    if not args.skip_parser:
        check_prerequisites()

    # Phase 2: Run Multiverse-Parser (URDF → clean URDF)
    if not args.skip_parser:
        env = resolve_package_uri_env(args.ros_package)
        run_multiverse_parser(input_urdf, clean_urdf, env)
    else:
        if not clean_urdf.exists():
            print(f"[ERROR] --skip-parser specified but {clean_urdf} does not exist.")
            sys.exit(1)
        print(f"[SKIP] Using existing: {clean_urdf}")

    # Phase 3: Copy meshes and rewrite paths to relative
    copy_meshes(clean_urdf, robot_name)

    # Phase 4: Extract info and generate Simox wrapper
    urdf_info = extract_urdf_info(clean_urdf)
    print(f"\n[INFO] Robot name  : {urdf_info['robot_name']}")
    print(f"[INFO] Root link   : {urdf_info['root_link']}")
    print(f"[INFO] Total links : {len(urdf_info['links'])}")

    if simox_wrapper.exists():
        print(f"\n[SKIP] Simox wrapper already exists: {simox_wrapper}")
        print("       Delete it to regenerate.")
    else:
        generate_simox_wrapper(
            robot_name=robot_name,
            clean_urdf_filename=clean_urdf.name,
            urdf_info=urdf_info,
            output_path=simox_wrapper
        )

    print("\n=== Conversion Complete ===")
    print(f"\nNext steps:")
    print(f"  1. Edit {simox_wrapper}")
    print(f"     Fill in EEF/chain info (see TODO comments inside)")
    print(f"  2. Test loading:")
    print(f"     export LD_LIBRARY_PATH=/home/zakaria/local/simox-urdf/lib:$LD_LIBRARY_PATH")
    print(f"     ./reproduce_urdf_fail {simox_wrapper}")
    print(f"  3. Run the service with PR2:")
    print(f"     ros2 run grasp_planner_service grasp_planner_service_node")


if __name__ == "__main__":
    main()
