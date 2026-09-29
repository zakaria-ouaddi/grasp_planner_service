#include <iostream>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/EndEffector/EndEffectorActor.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/Import/URDF/SimoxURDFFactory.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>

class MyPlanner : public GraspStudio::GenericGraspPlanner {
public:
    MyPlanner(VirtualRobot::GraspSetPtr graspSet,
              GraspStudio::GraspQualityMeasurePtr graspQuality,
              GraspStudio::ApproachMovementGeneratorPtr approach,
              float minQuality,
              bool forceClosure)
        : GenericGraspPlanner(graspSet, graspQuality, approach, minQuality, forceClosure) {}

    void testOne() {
        bool bRes = approach->setEEFToRandomApproachPose();
        if (!bRes) {
            std::cout << "setEEFToRandomApproachPose failed" << std::endl;
            return;
        }

        std::cout << "--- EEF details ---" << std::endl;
        auto rob = eef->getRobot();
        std::cout << "GCP: " << eef->getGCP()->getName() << ", Global Pos: "
                  << eef->getGCP()->getGlobalPose().block(0,3,3,1).transpose() << std::endl;
        auto l_distal = rob->getRobotNode("hand_l_distal_link");
        auto r_distal = rob->getRobotNode("hand_r_distal_link");
        if (l_distal && r_distal) {
            std::cout << "Left distal pos:  " << l_distal->getGlobalPose().block(0,3,3,1).transpose() << std::endl;
            std::cout << "Right distal pos: " << r_distal->getGlobalPose().block(0,3,3,1).transpose() << std::endl;
        }

        auto c1 = eef->closeActors(object);
        std::cout << "After closeActors, joints:" << std::endl;
        for (auto actor : eef->getActors()) {
            std::cout << " Actor: " << actor->getName() << std::endl;
            for (auto node : actor->getRobotNodes()) {
                std::cout << "   " << node->getName() << " = " << node->getJointValue() << std::endl;
            }
        }
        if (l_distal && r_distal) {
            std::cout << "Closed Left distal pos:  " << l_distal->getGlobalPose().block(0,3,3,1).transpose() << std::endl;
            std::cout << "Closed Right distal pos: " << r_distal->getGlobalPose().block(0,3,3,1).transpose() << std::endl;
        }

        eef->addStaticPartContacts(object, c1, approach->getApproachDirGlobal());

        if (retreatOnLowContacts && c1.size() < 2) {
            if (moveEEFAway(approach->getApproachDirGlobal(), 5.0f, 10)) {
                auto c2 = eef->closeActors(object);
                eef->addStaticPartContacts(object, c2, approach->getApproachDirGlobal());
                c1 = c2;
            }
        }

        std::cout << "Contacts count: " << c1.size() << std::endl;
        for (size_t ci = 0; ci < c1.size(); ++ci) {
            std::cout << "  Contact " << ci << " on " << c1[ci].robotNode->getName() << ": pt=("
                      << c1[ci].contactPointObstacleGlobal.transpose()
                      << "), dir=(" << c1[ci].approachDirectionGlobal.transpose() << ")" << std::endl;
        }
        if (c1.size() >= 2) {
            graspQuality->setContactPoints(c1);
            float score = graspQuality->getGraspQuality();
            bool fc = graspQuality->isGraspForceClosure();
            std::cout << "-> Score: " << score << ", FC: " << fc << std::endl;
        } else {
            std::cout << "-> FAILED: < 2 contacts" << std::endl;
        }

        approach->openHand();
    }
};

int main(int argc, char** argv) {
    VirtualRobot::RobotImporterFactoryPtr urdf_factory = VirtualRobot::SimoxURDFFactory::createInstance(nullptr);
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/robots");
    VirtualRobot::RuntimeEnvironment::addDataPath("/home/zakaria/grasp_planner/grasp_test_files/resources/objects");

    std::string robot_path = (argc > 1) ? argv[1] : "/home/zakaria/grasp_planner/grasp_test_files/resources/robots/tiago.xml";
    std::string eef_name = (argc > 2) ? argv[2] : "r_gripper";
    std::string preshape_name = (argc > 3) ? argv[3] : "Open";
    std::string object_path = (argc > 4) ? argv[4] : "/home/zakaria/grasp_planner/grasp_test_files/resources/objects/milk.xml";

    std::cout << "Loading robot: " << robot_path << std::endl;
    auto robot = VirtualRobot::RobotIO::loadRobot(robot_path);
    if (!robot) {
        std::cerr << "Failed to load robot: " << robot_path << std::endl;
        return 1;
    }

    std::cout << "Loading object: " << object_path << std::endl;
    auto object = VirtualRobot::ObjectIO::loadManipulationObject(object_path);
    if (!object) {
        std::cerr << "Failed to load object: " << object_path << std::endl;
        return 1;
    }
    object->setGlobalPose(Eigen::Matrix4f::Identity());

    auto eef = robot->getEndEffector(eef_name);
    if (!eef) {
        std::cerr << "EEF not found: " << eef_name << std::endl;
        return 1;
    }
    eef->setPreshape(preshape_name);

    auto palm = robot->getRobotNode("hand_palm_link");
    auto l_distal = robot->getRobotNode("hand_l_distal_link");
    auto r_distal = robot->getRobotNode("hand_r_distal_link");
    auto gcp = robot->getRobotNode("r_gripper_gcp");
    if (palm && l_distal && r_distal && gcp) {
        std::cout << "--- EEF in palm frame ---" << std::endl;
        std::cout << "GCP in palm: " << (palm->toLocalCoordinateSystem(gcp->getGlobalPose())).block(0,3,3,1).transpose() << std::endl;
        std::cout << "L distal in palm (open): " << (palm->toLocalCoordinateSystem(l_distal->getGlobalPose())).block(0,3,3,1).transpose() << std::endl;
        std::cout << "R distal in palm (open): " << (palm->toLocalCoordinateSystem(r_distal->getGlobalPose())).block(0,3,3,1).transpose() << std::endl;
        eef->setPreshape("Closed");
        std::cout << "L distal in palm (closed): " << (palm->toLocalCoordinateSystem(l_distal->getGlobalPose())).block(0,3,3,1).transpose() << std::endl;
        std::cout << "R distal in palm (closed): " << (palm->toLocalCoordinateSystem(r_distal->getGlobalPose())).block(0,3,3,1).transpose() << std::endl;
        eef->setPreshape(preshape_name);
    }

    auto qualityMeasure = std::make_shared<GraspStudio::GraspQualityMeasureWrenchSpace>(object);
    auto approach = std::make_shared<GraspStudio::ApproachMovementSurfaceNormal>(object, eef, preshape_name);
    qualityMeasure->calculateObjectProperties();

    auto grasps = std::make_shared<VirtualRobot::GraspSet>("test_grasps", robot->getType(), eef->getName());
    auto planner = std::make_shared<MyPlanner>(grasps, qualityMeasure, approach, 0.0f, false);
    planner->setVerbose(false);

    for (int i = 0; i < 10; ++i) {
        std::cout << "\n=== Test " << i << " ===" << std::endl;
        planner->testOne();
    }

    return 0;
}
