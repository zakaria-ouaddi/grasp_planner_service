// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "grasp_planner_msgs/srv/plan_grasp.hpp"


#ifndef GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__TRAITS_HPP_
#define GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "grasp_planner_msgs/srv/detail/plan_grasp__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'object_pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace grasp_planner_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlanGrasp_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_model_path
  {
    out << "robot_model_path: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_model_path, out);
    out << ", ";
  }

  // member: object_model_path
  {
    out << "object_model_path: ";
    rosidl_generator_traits::value_to_yaml(msg.object_model_path, out);
    out << ", ";
  }

  // member: object_pose
  {
    out << "object_pose: ";
    to_flow_style_yaml(msg.object_pose, out);
    out << ", ";
  }

  // member: end_effector_name
  {
    out << "end_effector_name: ";
    rosidl_generator_traits::value_to_yaml(msg.end_effector_name, out);
    out << ", ";
  }

  // member: kinematic_chain_name
  {
    out << "kinematic_chain_name: ";
    rosidl_generator_traits::value_to_yaml(msg.kinematic_chain_name, out);
    out << ", ";
  }

  // member: preshape_name
  {
    out << "preshape_name: ";
    rosidl_generator_traits::value_to_yaml(msg.preshape_name, out);
    out << ", ";
  }

  // member: quality_threshold
  {
    out << "quality_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.quality_threshold, out);
    out << ", ";
  }

  // member: timeout_ms
  {
    out << "timeout_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_ms, out);
    out << ", ";
  }

  // member: num_grasps_to_plan
  {
    out << "num_grasps_to_plan: ";
    rosidl_generator_traits::value_to_yaml(msg.num_grasps_to_plan, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlanGrasp_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_model_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_model_path: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_model_path, out);
    out << "\n";
  }

  // member: object_model_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_model_path: ";
    rosidl_generator_traits::value_to_yaml(msg.object_model_path, out);
    out << "\n";
  }

  // member: object_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_pose:\n";
    to_block_style_yaml(msg.object_pose, out, indentation + 2);
  }

  // member: end_effector_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "end_effector_name: ";
    rosidl_generator_traits::value_to_yaml(msg.end_effector_name, out);
    out << "\n";
  }

  // member: kinematic_chain_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kinematic_chain_name: ";
    rosidl_generator_traits::value_to_yaml(msg.kinematic_chain_name, out);
    out << "\n";
  }

  // member: preshape_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "preshape_name: ";
    rosidl_generator_traits::value_to_yaml(msg.preshape_name, out);
    out << "\n";
  }

  // member: quality_threshold
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "quality_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.quality_threshold, out);
    out << "\n";
  }

  // member: timeout_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timeout_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_ms, out);
    out << "\n";
  }

  // member: num_grasps_to_plan
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_grasps_to_plan: ";
    rosidl_generator_traits::value_to_yaml(msg.num_grasps_to_plan, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanGrasp_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace grasp_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use grasp_planner_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const grasp_planner_msgs::srv::PlanGrasp_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  grasp_planner_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use grasp_planner_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const grasp_planner_msgs::srv::PlanGrasp_Request & msg)
{
  return grasp_planner_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<grasp_planner_msgs::srv::PlanGrasp_Request>()
{
  return "grasp_planner_msgs::srv::PlanGrasp_Request";
}

template<>
inline const char * name<grasp_planner_msgs::srv::PlanGrasp_Request>()
{
  return "grasp_planner_msgs/srv/PlanGrasp_Request";
}

template<>
struct has_fixed_size<grasp_planner_msgs::srv::PlanGrasp_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<grasp_planner_msgs::srv::PlanGrasp_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'grasp_poses'
// already included above
// #include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace grasp_planner_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlanGrasp_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: error_message
  {
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << ", ";
  }

  // member: qualities
  {
    if (msg.qualities.size() == 0) {
      out << "qualities: []";
    } else {
      out << "qualities: [";
      size_t pending_items = msg.qualities.size();
      for (auto item : msg.qualities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: grasp_poses
  {
    if (msg.grasp_poses.size() == 0) {
      out << "grasp_poses: []";
    } else {
      out << "grasp_poses: [";
      size_t pending_items = msg.grasp_poses.size();
      for (auto item : msg.grasp_poses) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: are_force_closure
  {
    if (msg.are_force_closure.size() == 0) {
      out << "are_force_closure: []";
    } else {
      out << "are_force_closure: [";
      size_t pending_items = msg.are_force_closure.size();
      for (auto item : msg.are_force_closure) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlanGrasp_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: error_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << "\n";
  }

  // member: qualities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.qualities.size() == 0) {
      out << "qualities: []\n";
    } else {
      out << "qualities:\n";
      for (auto item : msg.qualities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: grasp_poses
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.grasp_poses.size() == 0) {
      out << "grasp_poses: []\n";
    } else {
      out << "grasp_poses:\n";
      for (auto item : msg.grasp_poses) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: are_force_closure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.are_force_closure.size() == 0) {
      out << "are_force_closure: []\n";
    } else {
      out << "are_force_closure:\n";
      for (auto item : msg.are_force_closure) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanGrasp_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace grasp_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use grasp_planner_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const grasp_planner_msgs::srv::PlanGrasp_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  grasp_planner_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use grasp_planner_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const grasp_planner_msgs::srv::PlanGrasp_Response & msg)
{
  return grasp_planner_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<grasp_planner_msgs::srv::PlanGrasp_Response>()
{
  return "grasp_planner_msgs::srv::PlanGrasp_Response";
}

template<>
inline const char * name<grasp_planner_msgs::srv::PlanGrasp_Response>()
{
  return "grasp_planner_msgs/srv/PlanGrasp_Response";
}

template<>
struct has_fixed_size<grasp_planner_msgs::srv::PlanGrasp_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<grasp_planner_msgs::srv::PlanGrasp_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace grasp_planner_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlanGrasp_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlanGrasp_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanGrasp_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace grasp_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use grasp_planner_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const grasp_planner_msgs::srv::PlanGrasp_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  grasp_planner_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use grasp_planner_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const grasp_planner_msgs::srv::PlanGrasp_Event & msg)
{
  return grasp_planner_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<grasp_planner_msgs::srv::PlanGrasp_Event>()
{
  return "grasp_planner_msgs::srv::PlanGrasp_Event";
}

template<>
inline const char * name<grasp_planner_msgs::srv::PlanGrasp_Event>()
{
  return "grasp_planner_msgs/srv/PlanGrasp_Event";
}

template<>
struct has_fixed_size<grasp_planner_msgs::srv::PlanGrasp_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Event>
  : std::integral_constant<bool, has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Request>::value && has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<grasp_planner_msgs::srv::PlanGrasp_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<grasp_planner_msgs::srv::PlanGrasp>()
{
  return "grasp_planner_msgs::srv::PlanGrasp";
}

template<>
inline const char * name<grasp_planner_msgs::srv::PlanGrasp>()
{
  return "grasp_planner_msgs/srv/PlanGrasp";
}

template<>
struct has_fixed_size<grasp_planner_msgs::srv::PlanGrasp>
  : std::integral_constant<
    bool,
    has_fixed_size<grasp_planner_msgs::srv::PlanGrasp_Request>::value &&
    has_fixed_size<grasp_planner_msgs::srv::PlanGrasp_Response>::value
  >
{
};

template<>
struct has_bounded_size<grasp_planner_msgs::srv::PlanGrasp>
  : std::integral_constant<
    bool,
    has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Request>::value &&
    has_bounded_size<grasp_planner_msgs::srv::PlanGrasp_Response>::value
  >
{
};

template<>
struct is_service<grasp_planner_msgs::srv::PlanGrasp>
  : std::true_type
{
};

template<>
struct is_service_request<grasp_planner_msgs::srv::PlanGrasp_Request>
  : std::true_type
{
};

template<>
struct is_service_response<grasp_planner_msgs::srv::PlanGrasp_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__TRAITS_HPP_
