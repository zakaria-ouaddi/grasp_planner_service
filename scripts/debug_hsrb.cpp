#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>
#include <VirtualRobot/IK/DifferentialIK.h>
#include <VirtualRobot/CollisionDetection/CDManager.h>

int main() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    auto robot = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/hsrb.xml");
    auto eef = robot->getEndEffector("r_gripper");
    auto object = VirtualRobot::ObjectIO::loadManipulationObject("/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml");
    object->setGlobalPose(Eigen::Matrix4f::Identity());

    auto qualityMeasure = std::make_shared<GraspStudio::GraspQualityMeasureWrenchSpace>(object);
    auto approach = std::make_shared<GraspStudio::ApproachMovementSurfaceNormal>(object, eef, "Open");
    qualityMeasure->calculateObjectProperties();

    auto grasps = std::make_shared<VirtualRobot::GraspSet>("grasps", robot->getType(), eef->getName());
    auto planner = std::make_shared<GraspStudio::GenericGraspPlanner>(grasps, qualityMeasure, approach, 0.0f, false);
    planner->setVerbose(false);
    planner->plan(25, 10000);

    Eigen::Matrix4f objPose = Eigen::Matrix4f::Identity();
    objPose(0, 3) = 500.0f;
    objPose(1, 3) = 100.0f;
    objPose(2, 3) = 750.0f;
    object->setGlobalPose(objPose);

    auto rns = robot->getRobotNodeSet("Arm");
    auto ikSolver = std::make_shared<VirtualRobot::DifferentialIK>(rns);
    auto cdManager = std::make_shared<VirtualRobot::CDManager>();
    auto rnsColModel = std::make_shared<VirtualRobot::SceneObjectSet>("col");
    for (auto node : rns->getAllRobotNodes()) {
        rnsColModel->addSceneObject(node);
    }
    cdManager->addCollisionModel(rnsColModel);

    robot->setJointValue("arm_lift_joint", 200.0f);
    robot->setJointValue("arm_flex_joint", -0.8f);
    robot->setJointValue("arm_roll_joint", 0.0f);
    robot->setJointValue("wrist_flex_joint", -0.6f);
    robot->setJointValue("wrist_roll_joint", 0.0f);
    auto seedValues = rns->getJointValues();

    int valid_count = 0;
    auto ikMode = (rns->getSize() >= 6) ? VirtualRobot::IKSolver::All : VirtualRobot::IKSolver::Position;

    for (size_t i = 0; i < grasps->getSize(); ++i) {
        rns->setJointValues(seedValues);
        auto grasp = grasps->getGrasp(i);
        Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
        if (global_tcp_pose(2, 2) > 0.5f) continue;

        ikSolver->setGoal(global_tcp_pose, rns->getTCP(), ikMode);
        if (!ikSolver->solveIK()) continue;
        if (cdManager->isInCollision(rnsColModel)) continue;

        valid_count++;
        std::cout << "Valid Grasp " << valid_count << ": Quality=" << grasp->getQuality()
                  << " Pos=(" << global_tcp_pose(0, 3)/1000.0f << ", "
                  << global_tcp_pose(1, 3)/1000.0f << ", "
                  << global_tcp_pose(2, 3)/1000.0f << ")" << std::endl;
    }
    std::cout << "Total Valid Grasps for HSR-B: " << valid_count << std::endl;
    return 0;
}
