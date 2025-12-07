// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "grasp_planner_msgs/srv/plan_grasp.hpp"


#ifndef GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__BUILDER_HPP_
#define GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "grasp_planner_msgs/srv/detail/plan_grasp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace grasp_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_PlanGrasp_Request_num_grasps_to_plan
{
public:
  explicit Init_PlanGrasp_Request_num_grasps_to_plan(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  ::grasp_planner_msgs::srv::PlanGrasp_Request num_grasps_to_plan(::grasp_planner_msgs::srv::PlanGrasp_Request::_num_grasps_to_plan_type arg)
  {
    msg_.num_grasps_to_plan = std::move(arg);
    return std::move(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_timeout_ms
{
public:
  explicit Init_PlanGrasp_Request_timeout_ms(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_num_grasps_to_plan timeout_ms(::grasp_planner_msgs::srv::PlanGrasp_Request::_timeout_ms_type arg)
  {
    msg_.timeout_ms = std::move(arg);
    return Init_PlanGrasp_Request_num_grasps_to_plan(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_quality_threshold
{
public:
  explicit Init_PlanGrasp_Request_quality_threshold(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_timeout_ms quality_threshold(::grasp_planner_msgs::srv::PlanGrasp_Request::_quality_threshold_type arg)
  {
    msg_.quality_threshold = std::move(arg);
    return Init_PlanGrasp_Request_timeout_ms(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_preshape_name
{
public:
  explicit Init_PlanGrasp_Request_preshape_name(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_quality_threshold preshape_name(::grasp_planner_msgs::srv::PlanGrasp_Request::_preshape_name_type arg)
  {
    msg_.preshape_name = std::move(arg);
    return Init_PlanGrasp_Request_quality_threshold(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_kinematic_chain_name
{
public:
  explicit Init_PlanGrasp_Request_kinematic_chain_name(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_preshape_name kinematic_chain_name(::grasp_planner_msgs::srv::PlanGrasp_Request::_kinematic_chain_name_type arg)
  {
    msg_.kinematic_chain_name = std::move(arg);
    return Init_PlanGrasp_Request_preshape_name(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_end_effector_name
{
public:
  explicit Init_PlanGrasp_Request_end_effector_name(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_kinematic_chain_name end_effector_name(::grasp_planner_msgs::srv::PlanGrasp_Request::_end_effector_name_type arg)
  {
    msg_.end_effector_name = std::move(arg);
    return Init_PlanGrasp_Request_kinematic_chain_name(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_object_pose
{
public:
  explicit Init_PlanGrasp_Request_object_pose(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_end_effector_name object_pose(::grasp_planner_msgs::srv::PlanGrasp_Request::_object_pose_type arg)
  {
    msg_.object_pose = std::move(arg);
    return Init_PlanGrasp_Request_end_effector_name(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_object_model_path
{
public:
  explicit Init_PlanGrasp_Request_object_model_path(::grasp_planner_msgs::srv::PlanGrasp_Request & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Request_object_pose object_model_path(::grasp_planner_msgs::srv::PlanGrasp_Request::_object_model_path_type arg)
  {
    msg_.object_model_path = std::move(arg);
    return Init_PlanGrasp_Request_object_pose(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

class Init_PlanGrasp_Request_robot_model_path
{
public:
  Init_PlanGrasp_Request_robot_model_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanGrasp_Request_object_model_path robot_model_path(::grasp_planner_msgs::srv::PlanGrasp_Request::_robot_model_path_type arg)
  {
    msg_.robot_model_path = std::move(arg);
    return Init_PlanGrasp_Request_object_model_path(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::grasp_planner_msgs::srv::PlanGrasp_Request>()
{
  return grasp_planner_msgs::srv::builder::Init_PlanGrasp_Request_robot_model_path();
}

}  // namespace grasp_planner_msgs


namespace grasp_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_PlanGrasp_Response_are_force_closure
{
public:
  explicit Init_PlanGrasp_Response_are_force_closure(::grasp_planner_msgs::srv::PlanGrasp_Response & msg)
  : msg_(msg)
  {}
  ::grasp_planner_msgs::srv::PlanGrasp_Response are_force_closure(::grasp_planner_msgs::srv::PlanGrasp_Response::_are_force_closure_type arg)
  {
    msg_.are_force_closure = std::move(arg);
    return std::move(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Response msg_;
};

class Init_PlanGrasp_Response_grasp_poses
{
public:
  explicit Init_PlanGrasp_Response_grasp_poses(::grasp_planner_msgs::srv::PlanGrasp_Response & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Response_are_force_closure grasp_poses(::grasp_planner_msgs::srv::PlanGrasp_Response::_grasp_poses_type arg)
  {
    msg_.grasp_poses = std::move(arg);
    return Init_PlanGrasp_Response_are_force_closure(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Response msg_;
};

class Init_PlanGrasp_Response_qualities
{
public:
  explicit Init_PlanGrasp_Response_qualities(::grasp_planner_msgs::srv::PlanGrasp_Response & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Response_grasp_poses qualities(::grasp_planner_msgs::srv::PlanGrasp_Response::_qualities_type arg)
  {
    msg_.qualities = std::move(arg);
    return Init_PlanGrasp_Response_grasp_poses(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Response msg_;
};

class Init_PlanGrasp_Response_error_message
{
public:
  explicit Init_PlanGrasp_Response_error_message(::grasp_planner_msgs::srv::PlanGrasp_Response & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Response_qualities error_message(::grasp_planner_msgs::srv::PlanGrasp_Response::_error_message_type arg)
  {
    msg_.error_message = std::move(arg);
    return Init_PlanGrasp_Response_qualities(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Response msg_;
};

class Init_PlanGrasp_Response_success
{
public:
  Init_PlanGrasp_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanGrasp_Response_error_message success(::grasp_planner_msgs::srv::PlanGrasp_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_PlanGrasp_Response_error_message(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::grasp_planner_msgs::srv::PlanGrasp_Response>()
{
  return grasp_planner_msgs::srv::builder::Init_PlanGrasp_Response_success();
}

}  // namespace grasp_planner_msgs


namespace grasp_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_PlanGrasp_Event_response
{
public:
  explicit Init_PlanGrasp_Event_response(::grasp_planner_msgs::srv::PlanGrasp_Event & msg)
  : msg_(msg)
  {}
  ::grasp_planner_msgs::srv::PlanGrasp_Event response(::grasp_planner_msgs::srv::PlanGrasp_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Event msg_;
};

class Init_PlanGrasp_Event_request
{
public:
  explicit Init_PlanGrasp_Event_request(::grasp_planner_msgs::srv::PlanGrasp_Event & msg)
  : msg_(msg)
  {}
  Init_PlanGrasp_Event_response request(::grasp_planner_msgs::srv::PlanGrasp_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PlanGrasp_Event_response(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Event msg_;
};

class Init_PlanGrasp_Event_info
{
public:
  Init_PlanGrasp_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanGrasp_Event_request info(::grasp_planner_msgs::srv::PlanGrasp_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_PlanGrasp_Event_request(msg_);
  }

private:
  ::grasp_planner_msgs::srv::PlanGrasp_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::grasp_planner_msgs::srv::PlanGrasp_Event>()
{
  return grasp_planner_msgs::srv::builder::Init_PlanGrasp_Event_info();
}

}  // namespace grasp_planner_msgs

#endif  // GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__BUILDER_HPP_
