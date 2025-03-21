// include/grasp_planner_service/grasp_planner_service.hpp
#ifndef GRASP_PLANNER_SERVICE_HPP
#define GRASP_PLANNER_SERVICE_HPP

#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"

// Simox includes
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/XML/ObjectIO.h>

// Simox forward declarations
namespace VirtualRobot {
typedef std::shared_ptr<Robot> RobotPtr;
typedef std::shared_ptr<ManipulationObject> ManipulationObjectPtr;
} // namespace VirtualRobot

namespace grasp_planner_service {

class GraspPlannerService : public rclcpp::Node {
  public:
    /**
     * @brief Constructor for the GraspPlannerService
     */
    GraspPlannerService();

    /**
     * @brief Destructor
     */
    ~GraspPlannerService() = default;

  private:
    /**
     * @brief Callback function for handling grasp planning service requests
     * @param request The service request containing robot and object
     * information
     * @param response The service response to be filled with grasp data
     */
    void handle_service(
        const std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Request>
            request,
        std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response);

    /**
     * @brief Loads a robot model from file
     * @param robot_model_path Path to the robot model file
     * @return Pointer to the loaded robot or nullptr if loading failed
     */
    VirtualRobot::RobotPtr loadRobot(const std::string &robot_model_path);

    /**
     * @brief Loads an object model from file
     * @param object_model_path Path to the object model file
     * @return Pointer to the loaded object or nullptr if loading failed
     */
    VirtualRobot::ManipulationObjectPtr
    loadObject(const std::string &object_model_path);

    // Service server member variable
    rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP
