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

void testPose(float x, float y, float z) {
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
    planner->plan(30, 10000);

    Eigen::Matrix4f objPose = Eigen::Matrix4f::Identity();
    objPose(0, 3) = x;
    objPose(1, 3) = y;
    objPose(2, 3) = z;
    object->setGlobalPose(objPose);

    auto rns = robot->getRobotNodeSet("Arm");
    auto ikSolver = std::make_shared<VirtualRobot::DifferentialIK>(rns);
    auto cdManager = std::make_shared<VirtualRobot::CDManager>();
    auto rnsColModel = std::make_shared<VirtualRobot::SceneObjectSet>("col");
    for (auto node : rns->getAllRobotNodes()) {
        rnsColModel->addSceneObject(node);
    }
    cdManager->addCollisionModel(rnsColModel);

    robot->setJointValue("joint_lift", z - 100.0f);
    robot->setJointValue("joint_arm_l0", 30.0f);
    robot->setJointValue("joint_arm_l1", 30.0f);
    robot->setJointValue("joint_arm_l2", 30.0f);
    robot->setJointValue("joint_arm_l3", 30.0f);
    auto seed = rns->getJointValues();

    int success = 0;
    for (size_t i = 0; i < grasps->getSize(); ++i) {
        rns->setJointValues(seed);
        auto grasp = grasps->getGrasp(i);
        Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
        if (global_tcp_pose(2, 2) > 0.5f) continue;
        ikSolver->setGoal(global_tcp_pose, rns->getTCP(), VirtualRobot::IKSolver::All);
        if (!ikSolver->solveIK()) continue;
        if (cdManager->isInCollision(rnsColModel)) continue;
        success++;
    }
    std::cout << "Pos (" << x << ", " << y << ", " << z << ") -> " << success << " grasps" << std::endl;
}

int main() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    testPose(0.0f, -400.0f, 700.0f);
    testPose(0.0f, -450.0f, 700.0f);
    testPose(0.0f, -500.0f, 700.0f);
    testPose(-50.0f, -450.0f, 700.0f);
    testPose(50.0f, -450.0f, 700.0f);
    testPose(0.0f, -450.0f, 650.0f);
    testPose(0.0f, -450.0f, 750.0f);
    return 0;
}
