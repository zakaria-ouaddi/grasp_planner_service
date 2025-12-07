import subprocess
import time
import os

# Object to test
object_file = "Vitalis.xml"
robot_model = "/home/zakaria/grasp_planner/grasp_test_files/ArmarIII-RightArm.xml"
objects_dir = "/home/zakaria/grasp_planner/grasp_test_files/objects"
object_path = os.path.join(objects_dir, object_file)

# Grid of poses to test
poses = [
    (0.5, 0.2, 0.2),   # Original
    (0.4, 0.1, 0.1),   # Closer, lower
    (0.4, 0.2, 0.1),
    (0.4, 0.0, 0.1),   # Centered Y
    (0.3, 0.1, 0.1),   # Very close
    (0.5, 0.0, 0.2),   # Centered Y, original height
    (0.6, 0.2, 0.2),   # Further away
    (0.4, -0.1, 0.1),  # Negative Y
]

def run_test(x, y, z):
    print(f"Testing pose: x={x}, y={y}, z={z}")
    
    cmd = [
        "ros2", "run", "grasp_planner_service", "test_grasp_planner",
        "--ros-args",
        "-p", f"robot_model_path:={robot_model}",
        "-p", f"object_model_path:={object_path}",
        "-p", "kinematic_chain_name:=RightArm",
        "-p", "end_effector_name:=Hand R",
        "-p", f"object_pose_x:={x}",
        "-p", f"object_pose_y:={y}",
        "-p", f"object_pose_z:={z}",
        "-p", "quality_threshold:=0.001",
        "-p", "num_grasps_to_plan:=100"
    ]
    
    try:
        # Run with a timeout of 40 seconds
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=40)
        output = result.stdout + result.stderr
        
        if "Successfully found" in output:
            print(f"SUCCESS! Found valid grasps at x={x}, y={y}, z={z}")
            return True
        else:
            print(f"Failed at x={x}, y={y}, z={z}")
            return False
            
    except subprocess.TimeoutExpired:
        print(f"Timeout testing pose x={x}, y={y}, z={z}")
        return False
    except Exception as e:
        print(f"Error testing pose: {e}")
        return False

def main():
    print(f"Starting pose search for {object_file}...")
    
    for (x, y, z) in poses:
        if run_test(x, y, z):
            break
    print("Search complete.")

if __name__ == "__main__":
    main()
