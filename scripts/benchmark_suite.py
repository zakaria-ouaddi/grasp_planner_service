#!/usr/bin/env python3
"""
Multi-Robot Grasp Planning Benchmark Suite.
Evaluates Simox grasp planning across 5 company robots (PR2, Tracy, TIAGo, HSR-B, Stretch)
and 5 company tabletop objects (milk, breakfast_cereal, bowl, spoon, jeroen_cup).
"""

import sys
import os
import time
import math
import csv
import argparse
from datetime import datetime
from collections import Counter

import yaml
import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp


def quat_to_rotation_matrix(q):
    """Convert geometry_msgs/Quaternion to 3x3 rotation matrix."""
    x, y, z, w = q.x, q.y, q.z, q.w
    return [
        [1 - 2 * (y * y + z * z),     2 * (x * y - z * w),     2 * (x * z + y * w)],
        [    2 * (x * y + z * w), 1 - 2 * (x * x + z * z),     2 * (y * z - x * w)],
        [    2 * (x * z - y * w),     2 * (y * z + x * w), 1 - 2 * (x * x + y * y)]
    ]


def classify_approach(orientation):
    """
    Classify the grasp approach direction based on Simox tool-frame Z forward vector.
    """
    R = quat_to_rotation_matrix(orientation)
    fwd_x = R[0][2]
    fwd_y = R[1][2]
    fwd_z = R[2][2]

    if fwd_z > 0.5:
        return 'bottom'
    elif fwd_z < -0.4:
        return 'top'

    if abs(fwd_x) >= abs(fwd_y):
        return 'front' if fwd_x >= 0 else 'back'
    else:
        return 'right' if fwd_y >= 0 else 'left'


class BenchmarkRunner(Node):
    def __init__(self, config_path):
        super().__init__('benchmark_runner')
        self.cli = self.create_client(PlanGrasp, 'plan_grasp')
        while not self.cli.wait_for_service(timeout_sec=2.0):
            self.get_logger().info('Waiting for /plan_grasp service...')

        with open(config_path, 'r') as f:
            self.config = yaml.safe_load(f)

        self.results = []

    def run_benchmark(self, robot_filter=None, object_filter=None):
        robots = self.config['robots']
        objects = self.config['objects']
        settings = self.config.get('planner_settings', {})
        timeout_ms = settings.get('timeout_ms', 10000)
        quality_thresh = settings.get('quality_threshold', 0.0)

        selected_robots = {k: v for k, v in robots.items() if not robot_filter or k == robot_filter}
        selected_objects = [o for o in objects if not object_filter or o['name'] == object_filter]

        total_pairs = len(selected_robots) * len(selected_objects)
        print(f"\n=======================================================")
        print(f" STARTING MULTI-ROBOT BENCHMARK ({total_pairs} Scenarios)")
        print(f" Robots:  {', '.join([v['name'] for v in selected_robots.values()])}")
        print(f" Objects: {', '.join([o['name'] for o in selected_objects])}")
        print(f"=======================================================\n")

        idx = 0
        for r_id, r_cfg in selected_robots.items():
            for obj in selected_objects:
                idx += 1
                obj_name = obj['name']
                print(f"[{idx:2d}/{total_pairs}] Testing {r_cfg['name']} on {obj_name}...", end="", flush=True)

                req = PlanGrasp.Request()
                req.robot_model_path = r_cfg['xml']
                req.object_model_path = obj['xml']
                req.end_effector_name = r_cfg['eef']
                req.kinematic_chain_name = r_cfg['chain']
                req.preshape_name = r_cfg['preshape']
                req.timeout_ms = timeout_ms
                req.num_grasps_to_plan = r_cfg.get('num_grasps', 25)
                req.quality_threshold = quality_thresh

                pos = r_cfg['obj_pos']
                req.object_pose.position.x = float(pos[0])
                req.object_pose.position.y = float(pos[1])
                req.object_pose.position.z = float(pos[2])
                req.object_pose.orientation.w = 1.0

                t0 = time.perf_counter()
                future = self.cli.call_async(req)
                rclpy.spin_until_future_complete(self, future)
                t_elapsed = time.perf_counter() - t0

                resp = future.result()
                success = resp.success if resp else False
                grasps = resp.grasp_poses if (resp and success) else []
                qualities = resp.qualities if (resp and success) else []
                force_closures = resp.are_force_closure if (resp and success) else []
                err_msg = resp.error_message if resp else "RPC failed"

                num_grasps = len(grasps)
                fc_count = sum(1 for fc in force_closures if fc)
                best_q = max(qualities) if qualities else 0.0
                mean_q = sum(qualities) / len(qualities) if qualities else 0.0

                approaches = [classify_approach(p.orientation) for p in grasps]
                approach_counts = dict(Counter(approaches))

                record = {
                    'robot_id': r_id,
                    'robot_name': r_cfg['name'],
                    'object': obj_name,
                    'category': obj.get('category', 'tabletop'),
                    'success': success,
                    'time_sec': round(t_elapsed, 3),
                    'grasps_returned': num_grasps,
                    'force_closure_count': fc_count,
                    'best_quality': round(best_q, 4),
                    'mean_quality': round(mean_q, 4),
                    'top_approaches': approach_counts.get('top', 0),
                    'front_approaches': approach_counts.get('front', 0),
                    'right_approaches': approach_counts.get('right', 0),
                    'left_approaches': approach_counts.get('left', 0),
                    'back_approaches': approach_counts.get('back', 0),
                    'bottom_approaches': approach_counts.get('bottom', 0),
                    'error_message': err_msg if not success else ""
                }
                self.results.append(record)

                if success:
                    print(f" -> PASS ({t_elapsed:.2f}s, {num_grasps} grasps, {fc_count} FC, best_q={best_q:.3f})")
                else:
                    print(f" -> FAIL ({t_elapsed:.2f}s, msg: {err_msg})")

        self.save_and_display_results()

    def save_and_display_results(self):
        log_dir = "/home/zakaria/grasp_planner/logs"
        os.makedirs(log_dir, exist_ok=True)
        timestamp_str = datetime.now().strftime("%Y%m%d_%H%M%S")
        ts_filename = os.path.join(log_dir, f"benchmark_5x5_{timestamp_str}.csv")
        latest_filename = os.path.join(log_dir, "benchmark_5x5_latest.csv")

        fieldnames = [
            'robot_id', 'robot_name', 'object', 'category', 'success',
            'time_sec', 'grasps_returned', 'force_closure_count',
            'best_quality', 'mean_quality', 'top_approaches', 'front_approaches',
            'right_approaches', 'left_approaches', 'back_approaches', 'bottom_approaches',
            'error_message'
        ]

        for fname in [ts_filename, latest_filename]:
            with open(fname, 'w', newline='') as f:
                writer = csv.DictWriter(f, fieldnames=fieldnames)
                writer.writeheader()
                writer.writerows(self.results)

        print(f"\nSaved benchmark results to:")
        print(f"  - {ts_filename}")
        print(f"  - {latest_filename}\n")

        # Display Markdown Summary Table
        print("### Multi-Robot Grasp Planning Benchmark Results (5x5 Matrix)\n")
        header = "| Robot | Object | Status | Time (s) | Grasps | FC Count | Best Qual | Mean Qual | Directions (T/F/R/L) |"
        sep = "|---|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|"
        print(header)
        print(sep)
        for r in self.results:
            status = "PASS" if r['success'] else "FAIL"
            dirs = f"T:{r['top_approaches']} F:{r['front_approaches']} R:{r['right_approaches']} L:{r['left_approaches']}"
            print(f"| {r['robot_name']} | {r['object']} | {status} | {r['time_sec']:.2f} | {r['grasps_returned']} | {r['force_closure_count']} | {r['best_quality']:.4f} | {r['mean_quality']:.4f} | {dirs} |")

        # Summary statistics
        total = len(self.results)
        passed = sum(1 for r in self.results if r['success'])
        total_grasps = sum(r['grasps_returned'] for r in self.results)
        avg_time = sum(r['time_sec'] for r in self.results) / total if total else 0.0

        print(f"\n**Summary:** {passed}/{total} scenarios successful ({(passed/total)*100:.1f}%). Total grasps planned: {total_grasps}. Average planning time: {avg_time:.2f}s per scenario.")


def main():
    parser = argparse.ArgumentParser(description="Multi-robot grasp planning benchmark.")
    parser.add_argument("--config", default="/home/zakaria/grasp_planner/scripts/benchmark_config.yaml")
    parser.add_argument("--robot", default=None, help="Filter by robot (pr2, tracy, tiago, hsrb, stretch)")
    parser.add_argument("--object", default=None, help="Filter by object (milk, breakfast_cereal, bowl, spoon, jeroen_cup)")
    args = parser.parse_args()

    rclpy.init()
    runner = BenchmarkRunner(args.config)
    try:
        runner.run_benchmark(robot_filter=args.robot, object_filter=args.object)
    finally:
        runner.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
