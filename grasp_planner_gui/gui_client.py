#!/usr/bin/env python3
import sys
import os
import threading
import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
import math
import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp

# --- ROS 2 Node Class ---
class GraspClientNode(Node):
    def __init__(self):
        super().__init__('grasp_planner_gui_client')
        self.client = self.create_client(PlanGrasp, 'plan_grasp')
        self.log_callback = None # Function to call for logging to GUI

    def log(self, msg):
        if self.log_callback:
            self.log_callback(msg)
        self.get_logger().info(msg)

    def send_request(self, params, result_callback):
        if not self.client.wait_for_service(timeout_sec=2.0):
            self.log("ERROR: Service 'plan_grasp' not available!")
            result_callback(None, "Service Unavailable")
            return

        req = PlanGrasp.Request()
        req.robot_model_path = params['robot_path']
        req.object_model_path = params['object_path']
        req.end_effector_name = params['eef_name']
        req.kinematic_chain_name = params['chain_name']
        req.preshape_name = params['preshape']
        
        req.object_pose.position.x = float(params['pose_x'])
        req.object_pose.position.y = float(params['pose_y'])
        req.object_pose.position.z = float(params['pose_z'])
        req.object_pose.orientation.x = float(params['quat_x'])
        req.object_pose.orientation.y = float(params['quat_y'])
        req.object_pose.orientation.z = float(params['quat_z'])
        req.object_pose.orientation.w = float(params['quat_w'])

        req.quality_threshold = float(params['quality'])
        req.timeout_ms = int(params['timeout'])
        req.num_grasps_to_plan = int(params['num_grasps'])

        self.log(f"Sending Request for {os.path.basename(req.object_model_path)}...")
        
        future = self.client.call_async(req)
        future.add_done_callback(lambda future: result_callback(future, None))

# --- Main GUI Class ---
class GraspGUI:
    def __init__(self, root, ros_node):
        self.root = root
        self.node = ros_node
        self.node.log_callback = self.append_log
        
        self.root.title("Grasp Planner Client")
        self.root.geometry("600x750")

        # Variables
        self.robot_path = tk.StringVar(value="/home/zakaria/grasp_planner/grasp_test_files/robots/ArmarIII/ArmarIII.xml")
        self.object_path = tk.StringVar(value="/home/zakaria/grasp_planner/grasp_test_files/objects/test_cube.xml")
        self.eef_name = tk.StringVar(value="Hand R")
        self.chain_name = tk.StringVar(value="TorsoRightArm")
        self.preshape = tk.StringVar(value="Power Preshape")
        self.pose_x = tk.StringVar(value="0.5")
        self.pose_y = tk.StringVar(value="0.2")
        self.pose_z = tk.StringVar(value="0.8") # Updated default
        self.pose_roll = tk.StringVar(value="0.0")
        self.pose_pitch = tk.StringVar(value="0.0")
        self.pose_yaw = tk.StringVar(value="0.0")
        self.quality = tk.StringVar(value="0.05")
        self.timeout = tk.StringVar(value="30000")
        self.num_grasps = tk.StringVar(value="50")

        self.create_widgets()

    def create_widgets(self):
        # File Selection Frame
        frame_files = tk.LabelFrame(self.root, text="Model Files", padx=10, pady=10)
        frame_files.pack(fill="x", padx=10, pady=5)

        self.add_file_selector(frame_files, "Robot XML:", self.robot_path)
        self.add_file_selector(frame_files, "Object XML:", self.object_path)

        # Parameters Frame
        frame_params = tk.LabelFrame(self.root, text="Planner Configuration", padx=10, pady=10)
        frame_params.pack(fill="x", padx=10, pady=5)

        self.add_entry(frame_params, "End Effector:", self.eef_name)
        self.add_entry(frame_params, "Kinematic Chain:", self.chain_name)
        self.add_entry(frame_params, "Preshape Name:", self.preshape)
        self.add_entry(frame_params, "Quality Threshold:", self.quality)
        self.add_entry(frame_params, "Timeout (ms):", self.timeout)
        self.add_entry(frame_params, "Num Grasps:", self.num_grasps)

        # Pose Frame
        frame_pose = tk.LabelFrame(self.root, text="Object Pose (World)", padx=10, pady=10)
        frame_pose.pack(fill="x", padx=10, pady=5)
        
        # Position
        f_pos = tk.Frame(frame_pose)
        f_pos.pack(pady=2)
        tk.Label(f_pos, text="Pos (m):").pack(side="left")
        tk.Label(f_pos, text="X").pack(side="left", padx=(5,0))
        tk.Entry(f_pos, textvariable=self.pose_x, width=6).pack(side="left")
        tk.Label(f_pos, text="Y").pack(side="left", padx=(5,0))
        tk.Entry(f_pos, textvariable=self.pose_y, width=6).pack(side="left")
        tk.Label(f_pos, text="Z").pack(side="left", padx=(5,0))
        tk.Entry(f_pos, textvariable=self.pose_z, width=6).pack(side="left")

        # Orientation (RPY)
        f_ori = tk.Frame(frame_pose)
        f_ori.pack(pady=2)
        tk.Label(f_ori, text="Ori (rad):").pack(side="left")
        tk.Label(f_ori, text="R").pack(side="left", padx=(5,0))
        tk.Entry(f_ori, textvariable=self.pose_roll, width=6).pack(side="left")
        tk.Label(f_ori, text="P").pack(side="left", padx=(5,0))
        tk.Entry(f_ori, textvariable=self.pose_pitch, width=6).pack(side="left")
        tk.Label(f_ori, text="Y").pack(side="left", padx=(5,0))
        tk.Entry(f_ori, textvariable=self.pose_yaw, width=6).pack(side="left")

        # Buttons
        btn_frame = tk.Frame(self.root, pady=10)
        btn_frame.pack()
        tk.Button(btn_frame, text="Plan Grasps", command=self.on_plan, bg="green", fg="white", font=("Arial", 12, "bold"), width=15).pack()

        # Log Area
        tk.Label(self.root, text="Logs / Results:").pack(anchor="w", padx=10)
        self.log_area = scrolledtext.ScrolledText(self.root, height=15)
        self.log_area.pack(fill="both", expand=True, padx=10, pady=5)

    def add_file_selector(self, parent, label, var):
        f = tk.Frame(parent)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=label, width=12, anchor="w").pack(side="left")
        tk.Entry(f, textvariable=var).pack(side="left", fill="x", expand=True, padx=5)
        tk.Button(f, text="...", command=lambda: self.browse_file(var), width=3).pack(side="right")

    def add_entry(self, parent, label, var):
        f = tk.Frame(parent)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=label, width=15, anchor="w").pack(side="left")
        tk.Entry(f, textvariable=var).pack(side="left", fill="x", expand=True)

    def browse_file(self, var):
        path = filedialog.askopenfilename(filetypes=[("XML Files", "*.xml"), ("All Files", "*.*")])
        if path:
            var.set(path)

    def append_log(self, text):
        self.log_area.insert(tk.END, text + "\n")
        self.log_area.see(tk.END)

    def euler_to_quaternion(self, roll, pitch, yaw):
        qx = math.sin(roll/2) * math.cos(pitch/2) * math.cos(yaw/2) - math.cos(roll/2) * math.sin(pitch/2) * math.sin(yaw/2)
        qy = math.cos(roll/2) * math.sin(pitch/2) * math.cos(yaw/2) + math.sin(roll/2) * math.cos(pitch/2) * math.sin(yaw/2)
        qz = math.cos(roll/2) * math.cos(pitch/2) * math.sin(yaw/2) - math.sin(roll/2) * math.sin(pitch/2) * math.cos(yaw/2)
        qw = math.cos(roll/2) * math.cos(pitch/2) * math.cos(yaw/2) + math.sin(roll/2) * math.sin(pitch/2) * math.sin(yaw/2)
        return [qx, qy, qz, qw]

    def on_plan(self):
        try:
            roll = float(self.pose_roll.get())
            pitch = float(self.pose_pitch.get())
            yaw = float(self.pose_yaw.get())
            quat = self.euler_to_quaternion(roll, pitch, yaw)
        except ValueError:
            self.append_log("ERROR: Invalid Orientation Values")
            return

        params = {
            'robot_path': self.robot_path.get(),
            'object_path': self.object_path.get(),
            'eef_name': self.eef_name.get(),
            'chain_name': self.chain_name.get(),
            'preshape': self.preshape.get(),
            'pose_x': self.pose_x.get(),
            'pose_y': self.pose_y.get(),
            'pose_z': self.pose_z.get(),
            'quat_x': quat[0],
            'quat_y': quat[1],
            'quat_z': quat[2],
            'quat_w': quat[3],
            'quality': self.quality.get(),
            'timeout': self.timeout.get(),
            'num_grasps': self.num_grasps.get()
        }
        
        self.append_log("-" * 30)
        self.node.send_request(params, self.handle_result)

    def handle_result(self, future, error_msg):
        # Runs in ROS thread, need to schedule GUI update
        if error_msg:
            self.root.after(0, lambda: self.append_log(f"FAIL: {error_msg}"))
            return

        try:
            response = future.result()
            msg = ""
            if response.success:
                num = len(response.grasp_poses)
                msg += f"SUCCESS: Found {num} valid grasps!\n"
                if num > 0:
                    best = response.qualities[0]
                    msg += f"Best Quality: {best:.4f}\n"
                    p = response.grasp_poses[0].position
                    msg += f"Top Pose: ({p.x:.2f}, {p.y:.2f}, {p.z:.2f})"
            else:
                msg += f"FAILURE: {response.error_message}"
            
            self.root.after(0, lambda: self.append_log(msg))
            
        except Exception as e:
            self.root.after(0, lambda: self.append_log(f"EXCEPTION: {e}"))

# --- Threading Setup ---
def run_ros(node):
    rclpy.spin(node)

def main():
    rclpy.init()
    node = GraspClientNode()
    
    # Run ROS in separate thread
    ros_thread = threading.Thread(target=run_ros, args=(node,), daemon=True)
    ros_thread.start()

    # Run GUI in main thread
    root = tk.Tk()
    app = GraspGUI(root, node)
    
    try:
        root.mainloop()
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()
