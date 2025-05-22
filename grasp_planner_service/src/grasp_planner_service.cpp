// src/grasp_planner_service.cpp
#include "grasp_planner_service/grasp_planner_service.hpp"

namespace grasp_planner_service {

GraspPlannerService::GraspPlannerService() : Node("grasp_planner_service") {
    service_ = this->create_service<grasp_planner_msgs::srv::PlanGrasp>(
        "plan_grasp", std::bind(&GraspPlannerService::handle_service, this,
                                std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Grasp Planner Service is ready");
}

void GraspPlannerService::handle_service(
    const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request> request,
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response) {
    RCLCPP_INFO(this->get_logger(), "Received grasp planning request for %s",
                request->object_model_path.c_str());

    try {
        // Load the robot and object models
        robot = loadRobot(request->robot_model_path);
        if (!robot) {
            response->success = false;
            RCLCPP_INFO(this->get_logger(), "Failed to load robot model: %s",
                        request->robot_model_path.c_str());
            return;
        }

        // Get end effector
        VirtualRobot::EndEffectorPtr eef =
            getEndEffector(robot, request->end_effector_name);
        if (!eef) {
            response->success = false;
            return;
        }

        // Load object
        loadObject(request->object_model_path);
        if (!object) {
            response->success = false;
            return;
        }

        // Reset the grasp set to store the new grasps
        grasps.reset(new VirtualRobot::GraspSet(
            "planned_grasps", robot->getType(), eef->getName()));

        // Setup the planner
        float qualityThreshold =
            request->quality_threshold > 0.0 ? request->quality_threshold : 0.2;

        if (planner) {
            planner->setParameters(qualityThreshold, true);
        } else {
            planner.reset(new GraspStudio::GenericGraspPlanner(
                grasps, qualityMeasure, approach, qualityThreshold, true));
        }

        // Fill in the response with a dummy grasp pose
        response->grasp_pose.position.x = 0.0;
        response->grasp_pose.position.y = 0.0;
        response->grasp_pose.position.z = 0.0;
    } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Exception during grasp planning: %s",
                     e.what());
        response->success = false;
    }
}

VirtualRobot::RobotPtr
GraspPlannerService::loadRobot(const std::string &robot_model_path) {
    VirtualRobot::RobotPtr robot =
        VirtualRobot::RobotIO::loadRobot(robot_model_path);
    if (!robot) {
        RCLCPP_ERROR(this->get_logger(), "Failed to load robot model from: %s",
                     robot_model_path.c_str());
    }
    return robot;
}

void GraspPlannerService::loadObject(const std::string &object_model_path) {
    if (!object_model_path.empty()) {

        try {
            object = VirtualRobot::ObjectIO::loadManipulationObject(
                object_model_path);
        } catch (VirtualRobot::VirtualRobotException &e) {
            if (!object) {
                RCLCPP_ERROR(this->get_logger(),
                             "Failed to load object model from: %s",
                             object_model_path.c_str());
                RCLCPP_ERROR(this->get_logger(), "%s", e.what());
                object = nullptr;
            }
        }

        qualityMeasure.reset(
            new GraspStudio::GraspQualityMeasureWrenchSpace(object));
        qualityMeasure->calculateObjectProperties();
        approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(
            object, eef, preshape));
        eefCloned = approach->getEEFRobotClone();

        if (robot && eef) {
            std::string name = "Grasp Planner - ";
            name += eef->getName();
            grasps.reset(
                new VirtualRobot::GraspSet(name, robot->getType(), eefName));
        }

        planner.reset(new GraspStudio::GenericGraspPlanner(
            grasps, qualityMeasure, approach));
        planner->setVerbose(true);
    }
}

VirtualRobot::EndEffectorPtr
GraspPlannerService::getEndEffector(const VirtualRobot::RobotPtr &robot,
                                    const std::string &end_effector_name) {
    VirtualRobot::EndEffectorPtr eef = robot->getEndEffector(end_effector_name);
    if (!eef) {
        RCLCPP_ERROR(this->get_logger(), "End effector not found: %s",
                     end_effector_name.c_str());
    }
    return eef;
}

} // namespace grasp_planner_service
