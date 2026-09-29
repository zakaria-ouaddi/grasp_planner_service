#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_urdf>" << std::endl;
    return 1;
  }

  std::string robot_file = argv[1];
  std::string home_path = std::getenv("HOME");
  std::string test_files_path = home_path + "/grasp_planner/grasp_test_files";
  std::string pr2_path = test_files_path + "/iai_pr2";

  std::cout << "Adding data path: " << test_files_path << std::endl;
  VirtualRobot::RuntimeEnvironment::addDataPath(test_files_path);
  std::cout << "Adding data path: " << pr2_path << std::endl;
  VirtualRobot::RuntimeEnvironment::addDataPath(pr2_path);

  try {

    std::cout << "Attempting to load robot via RobotIO: " << robot_file
              << std::endl;
    // Use RobotIO instead of direct Factory to test registration
    VirtualRobot::RobotPtr robot = VirtualRobot::RobotIO::loadRobot(robot_file);

    if (robot) {
      std::cout << "SUCCESS: Robot loaded: " << robot->getName() << std::endl;
      if (robot->getEndEffector("l_gripper")) {
        std::cout << "SUCCESS: Found EndEffector 'l_gripper'" << std::endl;
      } else {
        std::cerr << "FAILURE: EndEffector 'l_gripper' not found!" << std::endl;
        return 1;
      }
      return 0;
    } else {
      std::cerr << "FAILURE: Robot failed to load (nullptr returned)."
                << std::endl;
      return 1;
    }
  } catch (const std::exception &e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
    return 1;
  }
}
