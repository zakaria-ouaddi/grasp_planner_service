// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "grasp_planner_msgs/srv/plan_grasp.h"


#ifndef GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_H_
#define GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_model_path'
// Member 'object_model_path'
// Member 'end_effector_name'
// Member 'kinematic_chain_name'
// Member 'preshape_name'
#include "rosidl_runtime_c/string.h"
// Member 'object_pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in srv/PlanGrasp in the package grasp_planner_msgs.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Request
{
  /// Request
  rosidl_runtime_c__String robot_model_path;
  rosidl_runtime_c__String object_model_path;
  /// ADDED: Object pose in the world
  geometry_msgs__msg__Pose object_pose;
  rosidl_runtime_c__String end_effector_name;
  /// ADDED: Kinematic chain for IK checks
  rosidl_runtime_c__String kinematic_chain_name;
  rosidl_runtime_c__String preshape_name;
  float quality_threshold;
  int32_t timeout_ms;
  /// ADDED: Number of grasps to find
  int32_t num_grasps_to_plan;
} grasp_planner_msgs__srv__PlanGrasp_Request;

// Struct for a sequence of grasp_planner_msgs__srv__PlanGrasp_Request.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Request__Sequence
{
  grasp_planner_msgs__srv__PlanGrasp_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} grasp_planner_msgs__srv__PlanGrasp_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'error_message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'qualities'
// Member 'are_force_closure'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'grasp_poses'
// already included above
// #include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in srv/PlanGrasp in the package grasp_planner_msgs.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Response
{
  bool success;
  /// ADDED: Descriptive error message
  rosidl_runtime_c__String error_message;
  /// CHANGED: These are now arrays
  rosidl_runtime_c__float__Sequence qualities;
  geometry_msgs__msg__Pose__Sequence grasp_poses;
  rosidl_runtime_c__boolean__Sequence are_force_closure;
} grasp_planner_msgs__srv__PlanGrasp_Response;

// Struct for a sequence of grasp_planner_msgs__srv__PlanGrasp_Response.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Response__Sequence
{
  grasp_planner_msgs__srv__PlanGrasp_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} grasp_planner_msgs__srv__PlanGrasp_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  grasp_planner_msgs__srv__PlanGrasp_Event__request__MAX_SIZE = 1
};
// response
enum
{
  grasp_planner_msgs__srv__PlanGrasp_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/PlanGrasp in the package grasp_planner_msgs.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Event
{
  service_msgs__msg__ServiceEventInfo info;
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence request;
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence response;
} grasp_planner_msgs__srv__PlanGrasp_Event;

// Struct for a sequence of grasp_planner_msgs__srv__PlanGrasp_Event.
typedef struct grasp_planner_msgs__srv__PlanGrasp_Event__Sequence
{
  grasp_planner_msgs__srv__PlanGrasp_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} grasp_planner_msgs__srv__PlanGrasp_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_H_
