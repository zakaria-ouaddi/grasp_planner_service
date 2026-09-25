#!/usr/bin/env python3
import sys
import argparse
import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp

def main():
    parser = argparse.ArgumentParser(description="Test grasp planning for a single robot.")
    parser.add_argument("--robot", default="tiago", help="Robot name (pr2, tracy, tiago, hsrb, stretch)")
    parser.add_argument("--object", default="milk", help="Object name (milk, breakfast_cereal, spoon, bowl, jeroen_cup)")
    parser.add_argument("--eef", default=None, help="End-effector name")
    parser.add_argument("--chain", default=None, help="Kinematic chain name")
    parser.add_argument("--preshape", default=None, help="Preshape name")
    parser.add_argument("--num-grasps", type=int, default=25)
    parser.add_argument("--quality", type=float, default=0.0)
    parser.add_argument("--timeout", type=int, default=10000)
    args = parser.parse_args()

    robot_configs = {
        "pr2": {
            "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml",
            "eef": "r_gripper",
            "chain": "RightArm",
            "preshape": "open",
            "obj_pos": (0.6, -0.2, 0.8),
        },
        "tracy": {
            "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml",
            "eef": "r_gripper",
            "chain": "RightArm",
            "preshape": "Power Preshape",
            "obj_pos": (0.6, -0.2, 0.8),
        },
        "tiago": {
            "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tiago.xml",
            "eef": "r_gripper",
            "chain": "RightArm",
            "preshape": "Open",
            "obj_pos": (0.6, -0.2, 0.8),
        },
        "hsrb": {
            "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/hsrb.xml",
            "eef": "r_gripper",
            "chain": "Arm",
            "preshape": "Open",
            "obj_pos": (0.5, 0.1, 0.75),
        },
        "stretch": {
            "xml": "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/stretch.xml",
            "eef": "r_gripper",
            "chain": "Arm",
            "preshape": "Open",
            "obj_pos": (0.0, -0.45, 0.7),
        },
    }

    cfg = robot_configs.get(args.robot)
    if not cfg:
        print(f"Unknown robot: {args.robot}")
        sys.exit(1)

    eef = args.eef or cfg["eef"]
    chain = args.chain or cfg["chain"]
    preshape = args.preshape or cfg["preshape"]
    robot_xml = cfg["xml"]
    object_xml = f"/home/zakaria/grasp_planner/grasp_test_files/resources/objects/{args.object}.xml"

    rclpy.init()
    node = Node(f'test_{args.robot}_client')
    client = node.create_client(PlanGrasp, 'plan_grasp')
    if not client.wait_for_service(timeout_sec=5.0):
        print("Service /plan_grasp not available!")
        sys.exit(1)

    req = PlanGrasp.Request()
    req.robot_model_path = robot_xml
    req.object_model_path = object_xml
    req.end_effector_name = eef
    req.kinematic_chain_name = chain
    req.preshape_name = preshape
    req.timeout_ms = args.timeout
    req.num_grasps_to_plan = args.num_grasps
    req.quality_threshold = args.quality

    req.object_pose.position.x = cfg["obj_pos"][0]
    req.object_pose.position.y = cfg["obj_pos"][1]
    req.object_pose.position.z = cfg["obj_pos"][2]
    req.object_pose.orientation.w = 1.0

    print(f"Calling /plan_grasp for {args.robot.upper()} (EEF: {eef}, Chain: {chain}, Preshape: {preshape}) on {args.object}...")
    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future)
    res = future.result()

    print(f"=== {args.robot.upper()} RESULT ===")
    print("Success:", res.success)
    print("Message:", res.error_message)
    print("Grasps returned:", len(res.grasp_poses))
    for i, (p, q, fc) in enumerate(zip(res.grasp_poses[:5], res.qualities[:5], res.are_force_closure[:5])):
        print(f"  Grasp {i+1}: Quality={q:.4f}, ForceClosure={fc}, Pos=({p.position.x:.3f}, {p.position.y:.3f}, {p.position.z:.3f})")

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
