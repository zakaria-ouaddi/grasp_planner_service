#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp
from geometry_msgs.msg import Pose, Quaternion
import yaml
import csv
import time
import math
import sys
import os
import glob
from statistics import mean

def euler_to_quaternion(roll, pitch, yaw):
    r = math.radians(roll)
    p = math.radians(pitch)
    y = math.radians(yaw)
    cy = math.cos(y * 0.5)
    sy = math.sin(y * 0.5)
    cp = math.cos(p * 0.5)
    sp = math.sin(p * 0.5)
    cr = math.cos(r * 0.5)
    sr = math.sin(r * 0.5)
    
    q = Quaternion()
    q.w = cr * cp * cy + sr * sp * sy
    q.x = sr * cp * cy - cr * sp * sy
    q.y = cr * sp * cy + sr * cp * sy
    q.z = cr * cp * sy - sr * sp * cy
    return q

class BenchmarkRunner(Node):
    def __init__(self):
        super().__init__('benchmark_runner')
        self.cli = self.create_client(PlanGrasp, 'plan_grasp')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info(' service not available, waiting again...')
        
        # Dynamic Paths
        # Dynamic Paths (Relative to this script file)
        # Script is in <repo>/scripts/
        script_dir = os.path.dirname(os.path.realpath(__file__))
        self.base_path = os.path.abspath(os.path.join(script_dir, '..'))
        
        self.objects_dir = os.path.join(self.base_path, 'grasp_test_files', 'objects')
        self.robot_path = os.path.join(self.base_path, 'grasp_test_files', 'robots', 'ArmarIII', 'ArmarIII.xml')
        
        self.results = []
        self.failures_timestamps = []
        self.successes_timestamps = []

    def find_all_objects(self):
        # Recursively find all xml files
        search_pattern = os.path.join(self.objects_dir, '**', '*.xml')
        files = glob.glob(search_pattern, recursive=True)
        # Filter out "robots" folder if it accidently got in there, or invalid files
        return [f for f in files if 'robot' not in f.lower()]

    def run_suite(self):
        objects = self.find_all_objects()
        self.get_logger().info(f"Found {len(objects)} objects in library.")
        
        # Rotations to test (Yaw)
        rotations = [0, 90, 180, 270]
        
        total_tests = len(objects) * len(rotations)
        self.get_logger().info(f"Starting Crawl: {total_tests} total grasp attempts.")

        start_time_global = time.time()

        for obj_path in objects:
            obj_name = os.path.basename(obj_path)
            self.get_logger().info(f"--- Testing Object: {obj_name} ---")
            
            for yaw in rotations:
                scenario_name = f"{obj_name}_Yaw{yaw}"
                
                req = PlanGrasp.Request()
                req.robot_model_path = self.robot_path
                req.object_model_path = obj_path
                req.end_effector_name = "Hand R"
                req.kinematic_chain_name = "TorsoRightArm"
                req.preshape_name = "Auto" # Phase 4 Improvement: Smart Selection
                req.timeout_ms = 5000 # Reduced from 30s for faster benchmarking
                req.num_grasps_to_plan = 50 # Increased yield as requested
                req.quality_threshold = 0.01

                # Standard testing pose
                req.object_pose.position.x = 0.05
                req.object_pose.position.y = 0.6
                req.object_pose.position.z = 0.9
                req.object_pose.orientation = euler_to_quaternion(0, 0, yaw)

                t0 = time.time()
                future = self.cli.call_async(req)
                rclpy.spin_until_future_complete(self, future)
                duration = time.time() - t0
                
                resp = future.result()
                success = resp.success
                
                # Metrics Collection
                timestamp = time.time()
                if success:
                    self.successes_timestamps.append(timestamp)
                else:
                    self.failures_timestamps.append(timestamp)

                # Record
                result_entry = {
                    'object': obj_name,
                    'yaw': yaw,
                    'success': success,
                    'time_sec': round(duration, 3),
                    'grasps_found': len(resp.grasp_poses),
                    'best_quality': resp.qualities[0] if (success and len(resp.qualities)>0) else 0.0,
                    'timestamp': timestamp
                }
                self.results.append(result_entry)
                
                status = "PASS" if success else "FAIL"
                print(f"  [{status}] Yaw {yaw}: {duration:.2f}s | {len(resp.grasp_poses)} grasps")

        self.calculate_advanced_metrics(start_time_global)
        self.save_report()

    def calculate_advanced_metrics(self, start_time):
        total_runs = len(self.results)
        success_count = len(self.successes_timestamps)
        fail_count = len(self.failures_timestamps)
        
        # 1. Success Rate
        success_rate = (success_count / total_runs) * 100 if total_runs > 0 else 0
        
        # 2. MTBF (Mean Time Between Failures)
        # Simplified: Total Operation Time / Number of Failures
        total_duration = time.time() - start_time
        mtbf = total_duration / fail_count if fail_count > 0 else total_duration
        
        # 3. RTO (Recovery Time Objective)
        # Avg time delta between a Failure and next Success
        recovery_times = []
        sorted_results = sorted(self.results, key=lambda x: x['timestamp'])
        
        for i in range(len(sorted_results)-1):
            if not sorted_results[i]['success'] and sorted_results[i+1]['success']:
                delta = sorted_results[i+1]['timestamp'] - sorted_results[i]['timestamp']
                recovery_times.append(delta)
        
        avg_rto = mean(recovery_times) if recovery_times else 0.0

        print("\n=== ADVANCED METRICS ===")
        print(f"Total Objects Tested: {len(self.results)/4}")
        print(f"Overall Success Rate: {success_rate:.1f}%")
        print(f"MTBF: {mtbf:.1f} seconds")
        print(f"Avg Recovery Time: {avg_rto:.1f} seconds")

    def save_report(self):
        log_dir = os.path.join(self.base_path, 'logs')
        os.makedirs(log_dir, exist_ok=True)
        filename = os.path.join(log_dir, 'benchmark_crawler_report.csv')
        
        with open(filename, 'w', newline='') as f:
            fieldnames = ['object', 'yaw', 'success', 'time_sec', 'grasps_found', 'best_quality', 'timestamp']
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(self.results)
        
        self.get_logger().info(f"Full Report saved to {filename}")

def main():
    rclpy.init()
    runner = BenchmarkRunner()
    runner.run_suite()
    runner.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
