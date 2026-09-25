#!/usr/bin/env python3
import sys
import os
import threading
import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import math
import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp

# --- Presets for Company Robots & Objects ---
ROBOT_PRESETS = {
    "PR2": {
        "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml",
        "eef": "r_gripper",
        "chain": "RightArm",
        "preshape": "open",
        "pose": (0.6, -0.2, 0.8),
        "num_grasps": 25,
        "quality": 0.01,
    },

    "Tracy": {
        "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml",
        "eef": "r_gripper",
        "chain": "RightArm",
        "preshape": "Power Preshape",
        "pose": (0.6, -0.2, 0.8),
        "num_grasps": 25,
        "quality": 0.0,
    },
    "TIAGo": {
        "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tiago.xml",
        "eef": "r_gripper",
        "chain": "RightArm",
        "preshape": "Open",
        "pose": (0.6, -0.2, 0.8),
        "num_grasps": 35,
        "quality": 0.0,
    },
    "HSR-B": {
        "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/hsrb.xml",
        "eef": "r_gripper",
        "chain": "Arm",
        "preshape": "Open",
        "pose": (0.5, 0.1, 0.75),
        "num_grasps": 25,
        "quality": 0.0,
    },
    "Stretch": {
        "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/stretch.xml",
        "eef": "r_gripper",
        "chain": "Arm",
        "preshape": "Open",
        "pose": (0.0, -0.45, 0.7),
        "num_grasps": 40,
        "quality": 0.0,
    },
}

OBJECT_PRESETS = {
    "apartment_bowl (Conical Bowl)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/apartment_bowl.xml",
    "bowl (Dish)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/bowl.xml",
    "milk (Carton)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml",
    "breakfast_cereal (Box)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/breakfast_cereal.xml",
    "spoon (Utensil)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/spoon.xml",
    "jeroen_cup (Cup)": "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/jeroen_cup.xml",
}


# --- ROS 2 Node Class ---
class GraspClientNode(Node):
    def __init__(self):
        super().__init__('grasp_planner_gui_client')
        self.client = self.create_client(PlanGrasp, 'plan_grasp')
        self.log_callback = None

    def log(self, msg):
        if self.log_callback:
            self.log_callback(msg)
        self.get_logger().info(msg)

    def send_request(self, params, result_callback):
        if not self.client.wait_for_service(timeout_sec=2.0):
            self.log("ERROR: Service '/plan_grasp' not available! Is grasp_planner_service_node running?")
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

        r_name = os.path.basename(req.robot_model_path)
        o_name = os.path.basename(req.object_model_path)
        self.log(f"Calling /plan_grasp: Robot={r_name}, Object={o_name}, EEF={req.end_effector_name}, Chain={req.kinematic_chain_name}, TargetPos=({req.object_pose.position.x:.2f}, {req.object_pose.position.y:.2f}, {req.object_pose.position.z:.2f})...")

        future = self.client.call_async(req)
        future.add_done_callback(lambda future: result_callback(future, None))


# --- Main GUI Class ---
class GraspGUI:
    def __init__(self, root, ros_node):
        self.root = root
        self.node = ros_node
        self.node.log_callback = self.append_log

        self.root.title("Simox Grasp Planner — Multi-Robot GUI Client")
        self.root.geometry("680x820")

        # Variables
        self.selected_robot = tk.StringVar(value="PR2")
        self.selected_object = tk.StringVar(value="milk (Carton)")

        default_robot = ROBOT_PRESETS["PR2"]
        self.robot_path = tk.StringVar(value=default_robot["xml"])
        self.object_path = tk.StringVar(value=OBJECT_PRESETS["milk (Carton)"])
        self.eef_name = tk.StringVar(value=default_robot["eef"])
        self.chain_name = tk.StringVar(value=default_robot["chain"])
        self.preshape = tk.StringVar(value=default_robot["preshape"])

        self.pose_x = tk.StringVar(value=str(default_robot["pose"][0]))
        self.pose_y = tk.StringVar(value=str(default_robot["pose"][1]))
        self.pose_z = tk.StringVar(value=str(default_robot["pose"][2]))
        self.pose_roll = tk.StringVar(value="0.0")
        self.pose_pitch = tk.StringVar(value="0.0")
        self.pose_yaw = tk.StringVar(value="0.0")

        self.quality = tk.StringVar(value=str(default_robot["quality"]))
        self.timeout = tk.StringVar(value="10000")
        self.num_grasps = tk.StringVar(value=str(default_robot["num_grasps"]))

        self.create_widgets()

    def create_widgets(self):
        # 1. Quick Presets Frame
        frame_presets = tk.LabelFrame(self.root, text="Quick Robot & Object Presets", padx=10, pady=8, font=("Arial", 10, "bold"))
        frame_presets.pack(fill="x", padx=10, pady=5)

        # Robot Preset Row
        f_rp = tk.Frame(frame_presets)
        f_rp.pack(fill="x", pady=2)
        tk.Label(f_rp, text="Robot Preset:", width=14, anchor="w", font=("Arial", 9, "bold")).pack(side="left")
        robot_combo = ttk.Combobox(f_rp, textvariable=self.selected_robot, values=list(ROBOT_PRESETS.keys()) + ["Custom"], state="readonly", width=25)
        robot_combo.pack(side="left", padx=5)
        robot_combo.bind("<<ComboboxSelected>>", self.on_robot_preset_changed)
        tk.Label(f_rp, text="(Auto-configures XML, EEF, Chain, Pose)", fg="gray").pack(side="left")

        # Object Preset Row
        f_op = tk.Frame(frame_presets)
        f_op.pack(fill="x", pady=2)
        tk.Label(f_op, text="Object Preset:", width=14, anchor="w", font=("Arial", 9, "bold")).pack(side="left")
        obj_combo = ttk.Combobox(f_op, textvariable=self.selected_object, values=list(OBJECT_PRESETS.keys()) + ["Custom"], state="readonly", width=25)
        obj_combo.pack(side="left", padx=5)
        obj_combo.bind("<<ComboboxSelected>>", self.on_object_preset_changed)
        tk.Label(f_op, text="(Auto-configures Object XML)", fg="gray").pack(side="left")

        # 2. Model Files Frame
        frame_files = tk.LabelFrame(self.root, text="Model Files (Simox XML)", padx=10, pady=8)
        frame_files.pack(fill="x", padx=10, pady=5)
        self.add_file_selector(frame_files, "Robot XML:", self.robot_path)
        self.add_file_selector(frame_files, "Object XML:", self.object_path)

        # 3. Parameters Frame
        frame_params = tk.LabelFrame(self.root, text="Planner & Kinematic Configuration", padx=10, pady=8)
        frame_params.pack(fill="x", padx=10, pady=5)

        grid_frame = tk.Frame(frame_params)
        grid_frame.pack(fill="x")

        self.add_grid_entry(grid_frame, "End Effector:", self.eef_name, row=0, col=0)
        self.add_grid_entry(grid_frame, "Kinematic Chain:", self.chain_name, row=0, col=1)
        self.add_grid_entry(grid_frame, "Preshape Name:", self.preshape, row=1, col=0)
        self.add_grid_entry(grid_frame, "Quality Threshold:", self.quality, row=1, col=1)
        self.add_grid_entry(grid_frame, "Timeout (ms):", self.timeout, row=2, col=0)
        self.add_grid_entry(grid_frame, "Num Grasps:", self.num_grasps, row=2, col=1)

        # 4. Pose Frame
        frame_pose = tk.LabelFrame(self.root, text="Target Object Pose in Robot Base Frame", padx=10, pady=8)
        frame_pose.pack(fill="x", padx=10, pady=5)

        f_coords = tk.Frame(frame_pose)
        f_coords.pack(fill="x", pady=2)

        tk.Label(f_coords, text="Position (m):", width=12, anchor="w", font=("Arial", 9, "bold")).pack(side="left")
        tk.Label(f_coords, text="X:").pack(side="left")
        tk.Entry(f_coords, textvariable=self.pose_x, width=7).pack(side="left", padx=2)
        tk.Label(f_coords, text="Y:").pack(side="left", padx=(6, 0))
        tk.Entry(f_coords, textvariable=self.pose_y, width=7).pack(side="left", padx=2)
        tk.Label(f_coords, text="Z:").pack(side="left", padx=(6, 0))
        tk.Entry(f_coords, textvariable=self.pose_z, width=7).pack(side="left", padx=2)

        tk.Label(f_coords, text="  |  Euler RPY (rad):", font=("Arial", 9, "bold")).pack(side="left", padx=(10, 0))
        tk.Label(f_coords, text="R:").pack(side="left")
        tk.Entry(f_coords, textvariable=self.pose_roll, width=5).pack(side="left", padx=2)
        tk.Label(f_coords, text="P:").pack(side="left")
        tk.Entry(f_coords, textvariable=self.pose_pitch, width=5).pack(side="left", padx=2)
        tk.Label(f_coords, text="Y:").pack(side="left")
        tk.Entry(f_coords, textvariable=self.pose_yaw, width=5).pack(side="left", padx=2)

        # 5. Buttons Frame
        btn_frame = tk.Frame(self.root, pady=8)
        btn_frame.pack()
        tk.Button(btn_frame, text="Plan Grasps", command=self.on_plan, bg="#2e7d32", fg="white", font=("Arial", 11, "bold"), width=16, height=1).pack(side="left", padx=10)
        tk.Button(btn_frame, text="Clear Logs", command=self.clear_logs, font=("Arial", 10), width=12).pack(side="left", padx=5)

        # 6. Log Area
        tk.Label(self.root, text="Execution Logs & Planned Grasps:").pack(anchor="w", padx=10)
        self.log_area = scrolledtext.ScrolledText(self.root, height=14, font=("Monospace", 9))
        self.log_area.pack(fill="both", expand=True, padx=10, pady=(2, 10))

    def on_robot_preset_changed(self, event=None):
        r_name = self.selected_robot.get()
        if r_name in ROBOT_PRESETS:
            cfg = ROBOT_PRESETS[r_name]
            self.robot_path.set(cfg["xml"])
            self.eef_name.set(cfg["eef"])
            self.chain_name.set(cfg["chain"])
            self.preshape.set(cfg["preshape"])
            self.pose_x.set(str(cfg["pose"][0]))
            self.pose_y.set(str(cfg["pose"][1]))
            self.pose_z.set(str(cfg["pose"][2]))
            self.num_grasps.set(str(cfg["num_grasps"]))
            self.quality.set(str(cfg["quality"]))
            self.append_log(f">> Switched Robot to [{r_name}]: EEF={cfg['eef']}, Chain={cfg['chain']}, Default Pos={cfg['pose']}")

    def on_object_preset_changed(self, event=None):
        o_name = self.selected_object.get()
        if o_name in OBJECT_PRESETS:
            xml_path = OBJECT_PRESETS[o_name]
            self.object_path.set(xml_path)
            self.append_log(f">> Switched Object to [{o_name}]: Path={os.path.basename(xml_path)}")

    def add_file_selector(self, parent, label, var):
        f = tk.Frame(parent)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=label, width=12, anchor="w").pack(side="left")
        tk.Entry(f, textvariable=var).pack(side="left", fill="x", expand=True, padx=5)
        tk.Button(f, text="...", command=lambda: self.browse_file(var), width=3).pack(side="right")

    def add_grid_entry(self, parent, label, var, row, col):
        f = tk.Frame(parent)
        f.grid(row=row, column=col, sticky="ew", padx=5, pady=2)
        tk.Label(f, text=label, width=15, anchor="w").pack(side="left")
        tk.Entry(f, textvariable=var, width=16).pack(side="left", fill="x", expand=True)

    def browse_file(self, var):
        path = filedialog.askopenfilename(filetypes=[("XML Files", "*.xml"), ("All Files", "*.*")])
        if path:
            var.set(path)

    def append_log(self, text):
        self.log_area.insert(tk.END, text + "\n")
        self.log_area.see(tk.END)

    def clear_logs(self):
        self.log_area.delete('1.0', tk.END)

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

        self.append_log("-" * 55)
        self.node.send_request(params, self.handle_result)

    def handle_result(self, future, error_msg):
        if error_msg:
            self.root.after(0, lambda: self.append_log(f"FAIL: {error_msg}"))
            return

        try:
            response = future.result()
            lines = []
            if response.success:
                num = len(response.grasp_poses)
                lines.append(f"SUCCESS: Found {num} reachable & collision-free grasps!")
                if num > 0:
                    fc_count = sum(1 for fc in response.are_force_closure if fc)
                    lines.append(f"Force Closure Grasps: {fc_count}/{num}")
                    best_q = max(response.qualities)
                    lines.append(f"Best Quality: {best_q:.4f}")
                    lines.append("Top Grasps:")
                    for i, (p, q, fc) in enumerate(zip(response.grasp_poses[:5], response.qualities[:5], response.are_force_closure[:5])):
                        lines.append(f"  [{i+1}] Quality={q:.4f}, ForceClosure={fc}, Pos=({p.position.x:.3f}, {p.position.y:.3f}, {p.position.z:.3f})")
            else:
                lines.append(f"FAILURE: {response.error_message}")

            full_msg = "\n".join(lines)
            self.root.after(0, lambda: self.append_log(full_msg))

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
