// include/grasp_planner_service/grasp_planner_service.hpp
#ifndef GRASP_PLANNER_SERVICE_HPP
#define GRASP_PLANNER_SERVICE_HPP

#include "grasp_planner_msgs/srv/plan_grasp.hpp"
#include "rclcpp/rclcpp.hpp"

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

    // Service server member variable
    rclcpp::Service<grasp_planner_msgs::srv::PlanGrasp>::SharedPtr service_;
};

} // namespace grasp_planner_service

#endif // GRASP_PLANNER_SERVICE_HPP
