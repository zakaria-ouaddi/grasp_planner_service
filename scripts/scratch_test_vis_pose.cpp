#include <iostream>
#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>

int main(int argc, char** argv) {
    VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RobotPtr robot = VirtualRobot::RobotIO::loadRobot("grasp_test_files/resources/robots/tracy.xml");
    for (auto node : robot->getRobotNodes()) {
        if (node->getVisualization()) {
            auto vis = node->getVisualization();
            Eigen::Matrix4f g = node->getGlobalPose();
            Eigen::Matrix4f vg = vis->getGlobalPose();
            Eigen::Matrix4f l = vis->getLocalPose();
            if ((g - vg).norm() > 1e-3) {
                std::cout << node->getName() << ": node global trans=(" << g(0,3) << ", " << g(1,3) << ", " << g(2,3) << ") "
                          << "vis global trans=(" << vg(0,3) << ", " << vg(1,3) << ", " << vg(2,3) << ") "
                          << "vis local trans=(" << l(0,3) << ", " << l(1,3) << ", " << l(2,3) << ")" << std::endl;
            }
        }
    }
    return 0;
}
