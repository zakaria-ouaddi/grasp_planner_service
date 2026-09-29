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
    auto r1 = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml");
    std::cout << "PR2 loaded: " << (r1 ? r1->getName() : "NULL") << std::endl;

    std::cout << "Loading Tracy..." << std::endl;
    auto r2 = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml");
    std::cout << "Tracy loaded: " << (r2 ? r2->getName() : "NULL") << std::endl;

    return 0;
}
