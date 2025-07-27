#ifndef GRASP_PLANNER_SERVICE_HPP
#define GRASP_PLANNER_SERVICE_HPP

#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <string>
#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/transform_broadcaster.h"

// Simox includes
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspPlanner/GenericGraspPlanner.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/GraspStudio.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/XML/RobotIO.h>

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
     */
    void loadObject(const std::string &object_model_path);

    /**
     * @brief Gets the end effector from the robot
     * @param robot The robot model
     * @param end_effector_name Name of the end effector
     * @return Pointer to the end effector or nullptr if not found
     */
    VirtualRobot::EndEffectorPtr
    getEndEffector(const VirtualRobot::RobotPtr &robot,
                   const std::string &end_effector_name);

    /**
     * @brief Loads and validates all required models
     */
    bool load_models(const std::string& robot_path, 
                    const std::string& object_path,
                    const std::string& eef_name);

    /**
     * @brief Initializes the grasp planner components
     */
    bool initialize_planner(float quality_threshold, const std::string& preshape_name);

    /**
     * @brief Executes grasp planning
     */
    bool plan_grasps(int timeout_ms);

    /**
     * @brief Processes and validates the planned grasps
     */
    void process_grasps(std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp::Response> response);

    /**
     * @brief Visualizes all candidate grasps
     */
    void visualize_grasps();

    /**
     * @brief Validates grasp in simulation
     */
    bool validate_in_simulation(VirtualRobot::GraspPtr grasp);

    /**
     * @brief Validates preshape configuration
     */
    bool validate_preshape(const std::string& preshape_name);

    // Core components
    VirtualRobot::RobotPtr robot;
    VirtualRobot::RobotPtr eefCloned;
    VirtualRobot::RobotPtr robotObject;
    VirtualRobot::GraspableSensorizedObjectPtr object;
    VirtualRobot::EndEffectorPtr eef;
    VirtualRobot::GraspSetPtr grasps;

    // Planning components
    GraspStudio::GraspQualityMeasureWrenchSpacePtr qualityMeasure;
    GraspStudio::ApproachMovementSurfaceNormalPtr approach;
    GraspStudio::GenericGraspPlannerPtr planner;

    // Configuration
    std::string robotFile;
    std::string eefName;
    std::string preshape;

    // ROS interfaces
    rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr grasps_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr markers_pub_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

    // State
    sensor_msgs::msg::JointState current_joint_state_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP
