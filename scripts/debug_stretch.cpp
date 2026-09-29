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

    auto robot = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/stretch.xml");
    auto eef = robot->getEndEffector("r_gripper");
    auto object = VirtualRobot::ObjectIO::loadManipulationObject("/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml");
    object->setGlobalPose(Eigen::Matrix4f::Identity());

    auto qualityMeasure = std::make_shared<GraspStudio::GraspQualityMeasureWrenchSpace>(object);
    auto approach = std::make_shared<GraspStudio::ApproachMovementSurfaceNormal>(object, eef, "Open");
    qualityMeasure->calculateObjectProperties();

    auto grasps = std::make_shared<VirtualRobot::GraspSet>("grasps", robot->getType(), eef->getName());
    auto planner = std::make_shared<GraspStudio::GenericGraspPlanner>(grasps, qualityMeasure, approach, 0.0f, false);
    planner->setVerbose(false);
    planner->plan(50, 10000);

    Eigen::Matrix4f objPose = Eigen::Matrix4f::Identity();
    objPose(0, 3) = 0.0f;
    objPose(1, 3) = -450.0f;
    objPose(2, 3) = 700.0f;
    object->setGlobalPose(objPose);

    auto rns = robot->getRobotNodeSet("Arm");
    std::cout << "Stretch RNS nodes:" << std::endl;
    for (auto n : rns->getAllRobotNodes()) {
        std::cout << "  " << n->getName() << " [" << n->getJointLimitLo() << ", " << n->getJointLimitHi() << "]" << std::endl;
    }

    auto ikSolver = std::make_shared<VirtualRobot::DifferentialIK>(rns);
    auto cdManager = std::make_shared<VirtualRobot::CDManager>();
    auto rnsColModel = std::make_shared<VirtualRobot::SceneObjectSet>("col");
    for (auto node : rns->getAllRobotNodes()) {
        rnsColModel->addSceneObject(node);
    }
    cdManager->addCollisionModel(rnsColModel);

    // Test with all joints 0:
    for (auto n : rns->getAllRobotNodes()) {
        robot->setJointValue(n->getName(), 0.0f);
    }
    auto seed0 = rns->getJointValues();

    int success0 = 0;
    for (size_t i = 0; i < grasps->getSize(); ++i) {
        rns->setJointValues(seed0);
        auto grasp = grasps->getGrasp(i);
        Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
        if (global_tcp_pose(2, 2) > 0.5f) continue;
        ikSolver->setGoal(global_tcp_pose, rns->getTCP(), VirtualRobot::IKSolver::All);
        if (!ikSolver->solveIK()) continue;
        if (cdManager->isInCollision(rnsColModel)) continue;
        success0++;
    }
    std::cout << "All-Zero Seed: " << success0 << " / " << grasps->getSize() << " grasps" << std::endl;

    // Test with seeded joints:
    robot->setJointValue("joint_lift", 500.0f);
    robot->setJointValue("joint_arm_l0", 30.0f);
    robot->setJointValue("joint_arm_l1", 30.0f);
    robot->setJointValue("joint_arm_l2", 30.0f);
    robot->setJointValue("joint_arm_l3", 30.0f);
    auto seed1 = rns->getJointValues();

    int success1 = 0;
    for (size_t i = 0; i < grasps->getSize(); ++i) {
        rns->setJointValues(seed1);
        auto grasp = grasps->getGrasp(i);
        Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
        if (global_tcp_pose(2, 2) > 0.5f) continue;
        ikSolver->setGoal(global_tcp_pose, rns->getTCP(), VirtualRobot::IKSolver::All);
        if (!ikSolver->solveIK()) continue;
        if (cdManager->isInCollision(rnsColModel)) continue;
        success1++;
    }
    std::cout << "Seeded Seed: " << success1 << " / " << grasps->getSize() << " grasps" << std::endl;

    return 0;
}
