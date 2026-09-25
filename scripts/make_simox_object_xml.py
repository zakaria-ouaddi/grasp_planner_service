#!/usr/bin/env python3
"""
make_simox_object_xml.py
========================
Converts a meter-scale STL file into a Simox ManipulationObject XML.

Problem solved:
  CoraPlex object STL files (breakfast_cereal.stl, milk.stl, etc.) are in METERS.
  Simox VirtualRobot internally works in MILLIMETERS.
  Without conversion, objects appear ~1000x smaller than reality and Simox finds
  no graspable surface normals → zero grasps generated.

Solution:
  1. Read the source STL (binary format).
  2. Multiply all vertex coordinates by 1000 (m → mm).
  3. Write a new binary STL in the output directory.
  4. Generate a Simox ManipulationObject XML referencing the scaled STL.

Usage:
  python3 scripts/make_simox_object_xml.py \\
      --stl coraplex/resources/objects/breakfast_cereal.stl \\
      --name breakfast_cereal \\
      --eef r_gripper \\
      --output grasp_test_files/resources/objects/

  python3 scripts/make_simox_object_xml.py \\
      --stl coraplex/resources/objects/milk.stl \\
      --name milk --eef r_gripper l_gripper
"""

import argparse
import os
import struct
import sys
from pathlib import Path


# ─── STL helpers ────────────────────────────────────────────────────────────

def read_binary_stl(path: Path):
    """
    Read a binary STL file.
    Returns (header: bytes, triangles: list[tuple[normal, v1, v2, v3]])
    Each vertex is a tuple (x, y, z) of floats.
    """
    with open(path, 'rb') as f:
        header = f.read(80)
        count = struct.unpack('<I', f.read(4))[0]
        triangles = []
        for _ in range(count):
            normal = struct.unpack('<3f', f.read(12))
            v1 = struct.unpack('<3f', f.read(12))
            v2 = struct.unpack('<3f', f.read(12))
            v3 = struct.unpack('<3f', f.read(12))
            attr = struct.unpack('<H', f.read(2))[0]
            triangles.append((normal, v1, v2, v3, attr))
    return header, triangles


def is_ascii_stl(path: Path) -> bool:
    with open(path, 'rb') as f:
        return f.read(5) == b'solid'


def convert_ascii_to_binary_stl(path: Path) -> tuple:
    """
    Parse an ASCII STL and return (header, triangles) in binary format.
    """
    header = b'Converted from ASCII STL by make_simox_object_xml' + b'\x00' * 30
    triangles = []
    with open(path, 'r') as f:
        content = f.read()
    lines = content.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if line.startswith('facet normal'):
            parts = line.split()
            normal = (float(parts[2]), float(parts[3]), float(parts[4]))
            verts = []
            i += 2  # skip 'outer loop'
            for _ in range(3):
                i += 1
                vparts = lines[i].strip().split()
                verts.append((float(vparts[1]), float(vparts[2]), float(vparts[3])))
            triangles.append((normal, verts[0], verts[1], verts[2], 0))
        i += 1
    return header, triangles


def detect_unit(triangles) -> str:
    """
    Heuristic: if max vertex coordinate is < 10, likely meters; otherwise mm.
    PR2-graspable objects are 5–30 cm → 0.05–0.3 in meters, 50–300 in mm.
    """
    max_coord = 0.0
    for tri in triangles[:1000]:  # sample first 1000 faces
        for v in tri[1:4]:
            max_coord = max(max_coord, abs(v[0]), abs(v[1]), abs(v[2]))
    if max_coord < 5.0:
        return 'meters'
    return 'millimeters'


def scale_triangles(triangles, scale: float):
    """Scale all vertex coordinates by `scale`. Normals are not scaled."""
    scaled = []
    for tri in triangles:
        normal, v1, v2, v3, attr = tri
        sv1 = (v1[0]*scale, v1[1]*scale, v1[2]*scale)
        sv2 = (v2[0]*scale, v2[1]*scale, v2[2]*scale)
        sv3 = (v3[0]*scale, v3[1]*scale, v3[2]*scale)
        scaled.append((normal, sv1, sv2, sv3, attr))
    return scaled


def write_binary_stl(path: Path, header: bytes, triangles):
    """Write triangles as a binary STL file."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, 'wb') as f:
        f.write(header[:80].ljust(80, b'\x00'))
        f.write(struct.pack('<I', len(triangles)))
        for normal, v1, v2, v3, attr in triangles:
            f.write(struct.pack('<3f', *normal))
            f.write(struct.pack('<3f', *v1))
            f.write(struct.pack('<3f', *v2))
            f.write(struct.pack('<3f', *v3))
            f.write(struct.pack('<H', attr))


# ─── XML generation ──────────────────────────────────────────────────────────

def generate_simox_xml(name: str, stl_filename: str, eef_names: list[str],
                       robot_type: str = 'PR2') -> str:
    """
    Generate a Simox ManipulationObject XML string.

    The <GraspSet> elements are intentionally empty — Simox's GenericGraspPlanner
    populates them at runtime when planning grasps for this object.
    """
    grasp_sets = '\n'.join(
        f'    <GraspSet name="Simox_{eef}" RobotType="{robot_type}" '
        f'EndEffector="{eef}"/>'
        for eef in eef_names
    )
    return f"""<?xml version="1.0" encoding="UTF-8" ?>
<!--
  Simox ManipulationObject: {name}
  Generated by make_simox_object_xml.py
  STL source: {stl_filename}  (pre-scaled to millimetres)
-->
<ManipulationObject name="{name}">
    <Visualization>
        <File type="stl">{stl_filename}</File>
    </Visualization>
    <CollisionModel>
        <File type="stl">{stl_filename}</File>
    </CollisionModel>
{grasp_sets}
</ManipulationObject>
"""


# ─── Main ────────────────────────────────────────────────────────────────────

def convert_object(stl_path: Path, name: str, eef_names: list[str],
                   output_dir: Path, robot_type: str = 'PR2',
                   force_scale: float | None = None) -> Path:
    """
    Full pipeline: read STL → detect/scale → write mm STL → write XML.
    Returns path to the generated XML file.
    """
    print(f"[make_simox_object_xml] Processing: {stl_path}")

    # 1. Read STL
    if is_ascii_stl(stl_path):
        print("  Detected ASCII STL, converting to binary...")
        header, triangles = convert_ascii_to_binary_stl(stl_path)
    else:
        header, triangles = read_binary_stl(stl_path)
    print(f"  Read {len(triangles)} triangles")

    # 2. Detect / apply unit scale
    if force_scale is not None:
        scale = force_scale
        unit_guess = f"forced (x{scale})"
    else:
        unit_guess = detect_unit(triangles)
        scale = 1000.0 if unit_guess == 'meters' else 1.0
    print(f"  Unit detected: {unit_guess} → scale factor {scale:.1f}")

    if scale != 1.0:
        triangles = scale_triangles(triangles, scale)

    # 3. Compute bounding box for sanity check
    max_c = 0.0
    min_c = float('inf')
    for tri in triangles:
        for v in tri[1:4]:
            max_c = max(max_c, abs(v[0]), abs(v[1]), abs(v[2]))
            min_c = min(min_c, abs(v[0]), abs(v[1]), abs(v[2]))
    print(f"  After scaling: coordinate range [{min_c:.1f}, {max_c:.1f}] mm")
    if max_c > 500.0:
        print(f"  WARNING: Object max dim > 500 mm — Simox service will reject it.")
        print(f"  Consider using --force-scale 1.0 if the STL is already in mm.")
    if max_c < 1.0:
        print(f"  WARNING: Object very small (< 1 mm). Check input units.")

    # 4. Write scaled STL
    stl_out_name = f"{name}_mm.stl"
    stl_out_path = output_dir / stl_out_name
    write_binary_stl(stl_out_path, header, triangles)
    print(f"  Written scaled STL: {stl_out_path}")

    # 5. Write XML
    xml_content = generate_simox_xml(name, stl_out_name, eef_names, robot_type)
    xml_path = output_dir / f"{name}.xml"
    xml_path.write_text(xml_content, encoding='utf-8')
    print(f"  Written Simox XML:  {xml_path}")

    return xml_path


def main():
    parser = argparse.ArgumentParser(
        description="Convert a meter-scale STL to a Simox ManipulationObject XML (mm)."
    )
    parser.add_argument('--stl', required=True,
                        help='Input STL file path')
    parser.add_argument('--name', required=True,
                        help='Object name (used for output files and XML name attr)')
    parser.add_argument('--eef', nargs='+', default=['r_gripper'],
                        help='End-effector name(s) for GraspSet entries (default: r_gripper)')
    parser.add_argument('--output', default='grasp_test_files/resources/objects',
                        help='Output directory (default: grasp_test_files/resources/objects)')
    parser.add_argument('--robot-type', default='PR2',
                        help='Robot type for GraspSet (default: PR2)')
    parser.add_argument('--force-scale', type=float, default=None,
                        help='Override auto-detected scale factor (e.g. 1000 for m→mm)')

    args = parser.parse_args()

    stl_path = Path(args.stl)
    if not stl_path.exists():
        print(f"ERROR: STL file not found: {stl_path}", file=sys.stderr)
        sys.exit(1)

    output_dir = Path(args.output)
    xml_path = convert_object(
        stl_path=stl_path,
        name=args.name,
        eef_names=args.eef,
        output_dir=output_dir,
        robot_type=args.robot_type,
        force_scale=args.force_scale,
    )
    print(f"\n[make_simox_object_xml] Done → {xml_path}")


if __name__ == '__main__':
    main()
