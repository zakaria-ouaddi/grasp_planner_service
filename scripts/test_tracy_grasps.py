import rclpy
from rclpy.node import Node
from grasp_planner_msgs.srv import PlanGrasp
from geometry_msgs.msg import Pose
import sys

def main():
    rclpy.init()
    node = Node('test_tracy_client')
    client = node.create_client(PlanGrasp, 'plan_grasp')
    if not client.wait_for_service(timeout_sec=5.0):
        print("Service not available!")
        sys.exit(1)
    
    req = PlanGrasp.Request()
    req.robot_model_path = "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml"
    req.object_model_path = "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml"
    req.end_effector_name = "r_gripper"
    req.kinematic_chain_name = "RightArm"
    req.preshape_name = "Power Preshape"
    req.timeout_ms = 10000
    req.num_grasps_to_plan = 20
    req.quality_threshold = 0.01

    # Place milk on table in front of Tracy
    req.object_pose.position.x = 0.6
    req.object_pose.position.y = -0.2
    req.object_pose.position.z = 0.8
    req.object_pose.orientation.w = 1.0

    print("Calling /plan_grasp for Tracy on milk.xml...")
    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future)
    res = future.result()

    print("=== TRACY GRASP PLANNING RESULT ===")
    print("Success:", res.success)
    print("Message:", res.error_message)
    print("Grasps returned:", len(res.grasp_poses))
    for i, (p, q, fc) in enumerate(zip(res.grasp_poses[:5], res.qualities[:5], res.are_force_closure[:5])):
        print(f"  Grasp {i+1}: Quality={q:.4f}, ForceClosure={fc}, Pos=({p.position.x:.3f}, {p.position.y:.3f}, {p.position.z:.3f})")
    
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
