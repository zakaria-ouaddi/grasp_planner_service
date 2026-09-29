#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>

int main() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    std::cout << "Loading PR2..." << std::endl;
    VirtualRobot::RobotPtr r = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml");
    std::cout << "PR2 loaded. Now resetting r to nullptr..." << std::endl;
    r = nullptr;
    std::cout << "PR2 destroyed successfully!" << std::endl;

    std::cout << "Loading Tracy..." << std::endl;
    r = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml");
    std::cout << "Tracy loaded: " << (r ? r->getName() : "NULL") << std::endl;
    r = nullptr;
    std::cout << "Tracy destroyed successfully!" << std::endl;

    return 0;
}
