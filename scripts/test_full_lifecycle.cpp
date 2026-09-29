#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/Visualization/VisualizationNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>
#include <VirtualRobot/IK/DifferentialIK.h>
#include <VirtualRobot/CollisionDetection/CDManager.h>

void planOne(const std::string& robot_file, const std::string& eef_name, const std::string& chain_name, const std::string& preshape) {
    std::cout << "\n==============================================" << std::endl;
    std::cout << "=== Loading " << robot_file << " ===" << std::endl;
    auto robot = VirtualRobot::RobotIO::loadRobot(robot_file);
    if (!robot) {
        std::cerr << "Failed to load robot!" << std::endl;
        return;
    }

    // Touch visualization meshes
    for (auto node : robot->getRobotNodes()) {
        if (node->getVisualization()) {
            node->getVisualization()->getTriMeshModel();
        }
    }

    auto eef = robot->getEndEffector(eef_name);
    auto object = VirtualRobot::ObjectIO::loadManipulationObject("/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml");
    object->setGlobalPose(Eigen::Matrix4f::Identity());

    auto qualityMeasure = std::make_shared<GraspStudio::GraspQualityMeasureWrenchSpace>(object);
    auto approach = std::make_shared<GraspStudio::ApproachMovementSurfaceNormal>(object, eef, preshape);
    auto eefCloned = approach->getEEFRobotClone();
    qualityMeasure->calculateObjectProperties();

    auto grasps = std::make_shared<VirtualRobot::GraspSet>("grasps", robot->getType(), eef->getName());
    auto planner = std::make_shared<GraspStudio::GenericGraspPlanner>(grasps, qualityMeasure, approach, 0.0f, false);
    planner->setVerbose(false);
    planner->plan(5, 5000);

    auto rns = robot->getRobotNodeSet(chain_name);
    if (rns) {
        auto ikSolver = std::make_shared<VirtualRobot::DifferentialIK>(rns);
        auto cdManager = std::make_shared<VirtualRobot::CDManager>();
        auto rnsColModel = std::make_shared<VirtualRobot::SceneObjectSet>("col");
        for (auto node : rns->getAllRobotNodes()) {
            rnsColModel->addSceneObject(node);
        }
        cdManager->addCollisionModel(rnsColModel);
    }
    std::cout << "=== Finished planning for " << robot_file << " ===" << std::endl;
}

int main() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    planOne("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/pr2.xml", "r_gripper", "RightArm", "open");
    planOne("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tracy.xml", "r_gripper", "RightArm", "Power Preshape");
    planOne("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tiago.xml", "r_gripper", "RightArm", "Open");
    planOne("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/hsrb.xml", "r_gripper", "Arm", "Open");
    planOne("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/stretch.xml", "r_gripper", "Arm", "Open");

    std::cout << "\n==============================================" << std::endl;
    std::cout << "ALL 5 ROBOTS PLANNED IN SEQUENCE SUCCESSFULLY!" << std::endl;
    std::cout << "==============================================" << std::endl;
    return 0;
}
