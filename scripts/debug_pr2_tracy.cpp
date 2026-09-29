#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>
#include <VirtualRobot/Visualization/TriMeshModel.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>

void test() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    std::cout << "--- 1. Loading PR2 ---" << std::endl;
    auto pr2 = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml");
    if (!pr2) {
        std::cerr << "PR2 failed to load" << std::endl;
        return;
    }

    std::cout << "--- 2. Touching PR2 visual meshes ---" << std::endl;
    for (auto node : pr2->getRobotNodes()) {
        if (node->getVisualization()) {
            auto mesh = node->getVisualization()->getTriMeshModel();
            if (mesh) {
                // Access vertices and faces like createMeshMarker does
                for (auto f : mesh->faces) {
                    if (f.id1 < mesh->vertices.size()) {
                        auto v = mesh->vertices[f.id1];
                    }
                }
            }
        }
    }

    std::cout << "--- 3. Resetting PR2 pointer ---" << std::endl;
    pr2.reset();

    std::cout << "--- 4. Loading Tracy ---" << std::endl;
    auto tracy = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml");
    if (!tracy) {
        std::cerr << "Tracy failed to load" << std::endl;
        return;
    }
    std::cout << "Tracy loaded successfully!" << std::endl;
}

int main() {
    test();
    return 0;
}
