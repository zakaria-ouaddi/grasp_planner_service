#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>
#include <VirtualRobot/IK/DifferentialIK.h>
#include <VirtualRobot/CollisionDetection/CDManager.h>

void testPose(float x, float y, float z, float torso = 0.0f) {
    auto robot = VirtualRobot::RobotIO::loadRobot("/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tiago.xml");
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
    objPose(0, 3) = x;
    objPose(1, 3) = y;
    objPose(2, 3) = z;
    object->setGlobalPose(objPose);

    auto rns = robot->getRobotNodeSet("RightArm");
    auto ikSolver = std::make_shared<VirtualRobot::DifferentialIK>(rns);
    auto cdManager = std::make_shared<VirtualRobot::CDManager>();
    auto rnsColModel = std::make_shared<VirtualRobot::SceneObjectSet>("col");
    for (auto node : rns->getAllRobotNodes()) {
        rnsColModel->addSceneObject(node);
    }
    cdManager->addCollisionModel(rnsColModel);

    if (torso > 0.0f && robot->hasRobotNode("torso_lift_joint")) {
        robot->setJointValue("torso_lift_joint", torso);
    }

    robot->setJointValue("arm_right_1_joint", 0.2f);
    robot->setJointValue("arm_right_2_joint", -0.4f);
    robot->setJointValue("arm_right_3_joint", -0.4f);
    robot->setJointValue("arm_right_4_joint", 1.5f);
    robot->setJointValue("arm_right_5_joint", -1.5f);
    robot->setJointValue("arm_right_6_joint", 0.0f);
    robot->setJointValue("arm_right_7_joint", 0.0f);
    auto seedValues = rns->getJointValues();

    int success = 0;
    for (size_t i = 0; i < grasps->getSize(); ++i) {
        rns->setJointValues(seedValues);
        auto grasp = grasps->getGrasp(i);
        Eigen::Matrix4f global_tcp_pose = grasp->getTcpPoseGlobal(object->getGlobalPose());
        if (global_tcp_pose(2, 2) > 0.5f) continue;
        ikSolver->setGoal(global_tcp_pose);
        if (!ikSolver->solveIK()) continue;
        if (cdManager->isInCollision(rnsColModel)) continue;
        success++;
    }
    std::cout << "Pos (" << x << ", " << y << ", " << z << ") Torso=" << torso << " -> " << success << " grasps" << std::endl;
}

int main() {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    testPose(600, -200, 800, 0.0f);
    testPose(500, -200, 800, 0.0f);
    testPose(500, -150, 750, 0.0f);
    testPose(550, -150, 750, 0.0f);
    testPose(550, -150, 750, 150.0f);
    testPose(600, -200, 800, 150.0f);
    return 0;
}
