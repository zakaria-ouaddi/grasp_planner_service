#include <iostream>
#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>
#include <VirtualRobot/Visualization/TriMeshModel.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    std::string xml = argv[1];
    VirtualRobot::RobotPtr robot = VirtualRobot::RobotIO::loadRobot(xml);
    if (!robot) {
        std::cerr << "Failed to load " << xml << std::endl;
        return 1;
    }
    std::cout << "Loaded robot: " << robot->getName() << std::endl;
    for (auto node : robot->getRobotNodes()) {
        if (node->getVisualization()) {
            auto mesh = node->getVisualization()->getTriMeshModel();
            if (mesh && !mesh->vertices.empty()) {
                Eigen::Vector3f min_v = mesh->vertices[0];
                Eigen::Vector3f max_v = mesh->vertices[0];
                for (const auto& v : mesh->vertices) {
                    min_v = min_v.cwiseMin(v);
                    max_v = max_v.cwiseMax(v);
                }
                Eigen::Vector3f ext = max_v - min_v;
                std::cout << "Node [" << node->getName() << "] mesh vertices=" << mesh->vertices.size()
                          << " extents=(" << ext.x() << ", " << ext.y() << ", " << ext.z() << ")"
                          << " min=(" << min_v.x() << ", " << min_v.y() << ", " << min_v.z() << ")"
                          << " max=(" << max_v.x() << ", " << max_v.y() << ", " << max_v.z() << ")"
                          << " globalPoseTrans=(" << node->getGlobalPose()(0,3) << ", "
                                                  << node->getGlobalPose()(1,3) << ", "
                                                  << node->getGlobalPose()(2,3) << ")"
                          << std::endl;
            }
        }
    }
    return 0;
}
