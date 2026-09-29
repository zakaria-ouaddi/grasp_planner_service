#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>

int main(int argc, char** argv) {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");

    std::string robot_path = (argc > 1) ? argv[1] : "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/stretch.xml";
    std::string chain_name = (argc > 2) ? argv[2] : "Arm";

    auto robot = VirtualRobot::RobotIO::loadRobot(robot_path);
    if (!robot) {
        std::cerr << "Failed to load " << robot_path << std::endl;
        return 1;
    }

    auto rns = robot->getRobotNodeSet(chain_name);
    if (!rns) {
        std::cerr << "RNS not found: " << chain_name << std::endl;
        return 1;
    }

    auto tcp = rns->getTCP();
    std::cout << "Robot: " << robot->getName() << std::endl;
    std::cout << "Chain: " << chain_name << ", TCP: " << (tcp ? tcp->getName() : "None") << std::endl;
    std::cout << "Joints in chain:" << std::endl;
    for (auto node : rns->getAllRobotNodes()) {
        std::cout << "  " << node->getName() << " [" << node->getJointLimitLo() << " .. " << node->getJointLimitHi() << "]" << std::endl;
    }

    // Default pose
    std::cout << "\nDefault TCP Global Pos: " << tcp->getGlobalPose().block(0,3,3,1).transpose() << std::endl;

    // Extend arm joints to mid
    for (auto node : rns->getAllRobotNodes()) {
        float mid = 0.5f * (node->getJointLimitLo() + node->getJointLimitHi());
        node->setJointValue(mid);
    }
    std::cout << "Mid-range TCP Global Pos: " << tcp->getGlobalPose().block(0,3,3,1).transpose() << std::endl;

    // Extend arm joints to max
    for (auto node : rns->getAllRobotNodes()) {
        node->setJointValue(node->getJointLimitHi());
    }
    std::cout << "Max-range TCP Global Pos: " << tcp->getGlobalPose().block(0,3,3,1).transpose() << std::endl;

    return 0;
}
