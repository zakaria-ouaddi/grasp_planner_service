// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "grasp_planner_msgs/srv/detail/plan_grasp__rosidl_typesupport_introspection_c.h"
#include "grasp_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"
#include "grasp_planner_msgs/srv/detail/plan_grasp__struct.h"


// Include directives for member types
// Member `robot_model_path`
// Member `object_model_path`
// Member `end_effector_name`
// Member `kinematic_chain_name`
// Member `preshape_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `object_pose`
#include "geometry_msgs/msg/pose.h"
// Member `object_pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  grasp_planner_msgs__srv__PlanGrasp_Request__init(message_memory);
}

void grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_fini_function(void * message_memory)
{
  grasp_planner_msgs__srv__PlanGrasp_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_member_array[9] = {
  {
    "robot_model_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, robot_model_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "object_model_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, object_model_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "object_pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, object_pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "end_effector_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, end_effector_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kinematic_chain_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, kinematic_chain_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "preshape_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, preshape_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "quality_threshold",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, quality_threshold),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timeout_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, timeout_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_grasps_to_plan",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Request, num_grasps_to_plan),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_members = {
  "grasp_planner_msgs__srv",  // message namespace
  "PlanGrasp_Request",  // message name
  9,  // number of fields
  sizeof(grasp_planner_msgs__srv__PlanGrasp_Request),
  false,  // has_any_key_member_
  grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_member_array,  // message members
  grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle = {
  0,
  &grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_members,
  get_message_typesupport_handle_function,
  &grasp_planner_msgs__srv__PlanGrasp_Request__get_type_hash,
  &grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description,
  &grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_grasp_planner_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Request)() {
  grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle.typesupport_identifier) {
    grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__rosidl_typesupport_introspection_c.h"
// already included above
// #include "grasp_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__struct.h"


// Include directives for member types
// Member `error_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `qualities`
// Member `are_force_closure`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `grasp_poses`
// already included above
// #include "geometry_msgs/msg/pose.h"
// Member `grasp_poses`
// already included above
// #include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  grasp_planner_msgs__srv__PlanGrasp_Response__init(message_memory);
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_fini_function(void * message_memory)
{
  grasp_planner_msgs__srv__PlanGrasp_Response__fini(message_memory);
}

size_t grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__qualities(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__qualities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__qualities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__qualities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__qualities(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__qualities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__qualities(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__qualities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__grasp_poses(
  const void * untyped_member)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return member->size;
}

const void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__grasp_poses(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__grasp_poses(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__grasp_poses(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Pose * item =
    ((const geometry_msgs__msg__Pose *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__grasp_poses(untyped_member, index));
  geometry_msgs__msg__Pose * value =
    (geometry_msgs__msg__Pose *)(untyped_value);
  *value = *item;
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__grasp_poses(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Pose * item =
    ((geometry_msgs__msg__Pose *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__grasp_poses(untyped_member, index));
  const geometry_msgs__msg__Pose * value =
    (const geometry_msgs__msg__Pose *)(untyped_value);
  *item = *value;
}

bool grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__grasp_poses(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  geometry_msgs__msg__Pose__Sequence__fini(member);
  return geometry_msgs__msg__Pose__Sequence__init(member, size);
}

size_t grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__are_force_closure(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__are_force_closure(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__are_force_closure(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__are_force_closure(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__are_force_closure(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__are_force_closure(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__are_force_closure(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__are_force_closure(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_member_array[5] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Response, error_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "qualities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Response, qualities),  // bytes offset in struct
    NULL,  // default value
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__qualities,  // size() function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__qualities,  // get_const(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__qualities,  // get(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__qualities,  // fetch(index, &value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__qualities,  // assign(index, value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__qualities  // resize(index) function pointer
  },
  {
    "grasp_poses",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Response, grasp_poses),  // bytes offset in struct
    NULL,  // default value
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__grasp_poses,  // size() function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__grasp_poses,  // get_const(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__grasp_poses,  // get(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__grasp_poses,  // fetch(index, &value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__grasp_poses,  // assign(index, value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__grasp_poses  // resize(index) function pointer
  },
  {
    "are_force_closure",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Response, are_force_closure),  // bytes offset in struct
    NULL,  // default value
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Response__are_force_closure,  // size() function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Response__are_force_closure,  // get_const(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Response__are_force_closure,  // get(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Response__are_force_closure,  // fetch(index, &value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Response__are_force_closure,  // assign(index, value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Response__are_force_closure  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_members = {
  "grasp_planner_msgs__srv",  // message namespace
  "PlanGrasp_Response",  // message name
  5,  // number of fields
  sizeof(grasp_planner_msgs__srv__PlanGrasp_Response),
  false,  // has_any_key_member_
  grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_member_array,  // message members
  grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle = {
  0,
  &grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_members,
  get_message_typesupport_handle_function,
  &grasp_planner_msgs__srv__PlanGrasp_Response__get_type_hash,
  &grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description,
  &grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_grasp_planner_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Response)() {
  grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle.typesupport_identifier) {
    grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__rosidl_typesupport_introspection_c.h"
// already included above
// #include "grasp_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "grasp_planner_msgs/srv/plan_grasp.h"
// Member `request`
// Member `response`
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  grasp_planner_msgs__srv__PlanGrasp_Event__init(message_memory);
}

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_fini_function(void * message_memory)
{
  grasp_planner_msgs__srv__PlanGrasp_Event__fini(message_memory);
}

size_t grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Event__request(
  const void * untyped_member)
{
  const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * member =
    (const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__request(
  const void * untyped_member, size_t index)
{
  const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * member =
    (const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__request(
  void * untyped_member, size_t index)
{
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * member =
    (grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const grasp_planner_msgs__srv__PlanGrasp_Request * item =
    ((const grasp_planner_msgs__srv__PlanGrasp_Request *)
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__request(untyped_member, index));
  grasp_planner_msgs__srv__PlanGrasp_Request * value =
    (grasp_planner_msgs__srv__PlanGrasp_Request *)(untyped_value);
  *value = *item;
}

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  grasp_planner_msgs__srv__PlanGrasp_Request * item =
    ((grasp_planner_msgs__srv__PlanGrasp_Request *)
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__request(untyped_member, index));
  const grasp_planner_msgs__srv__PlanGrasp_Request * value =
    (const grasp_planner_msgs__srv__PlanGrasp_Request *)(untyped_value);
  *item = *value;
}

bool grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Event__request(
  void * untyped_member, size_t size)
{
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * member =
    (grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *)(untyped_member);
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini(member);
  return grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init(member, size);
}

size_t grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Event__response(
  const void * untyped_member)
{
  const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * member =
    (const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__response(
  const void * untyped_member, size_t index)
{
  const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * member =
    (const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__response(
  void * untyped_member, size_t index)
{
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * member =
    (grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const grasp_planner_msgs__srv__PlanGrasp_Response * item =
    ((const grasp_planner_msgs__srv__PlanGrasp_Response *)
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__response(untyped_member, index));
  grasp_planner_msgs__srv__PlanGrasp_Response * value =
    (grasp_planner_msgs__srv__PlanGrasp_Response *)(untyped_value);
  *value = *item;
}

void grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  grasp_planner_msgs__srv__PlanGrasp_Response * item =
    ((grasp_planner_msgs__srv__PlanGrasp_Response *)
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__response(untyped_member, index));
  const grasp_planner_msgs__srv__PlanGrasp_Response * value =
    (const grasp_planner_msgs__srv__PlanGrasp_Response *)(untyped_value);
  *item = *value;
}

bool grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Event__response(
  void * untyped_member, size_t size)
{
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * member =
    (grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *)(untyped_member);
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini(member);
  return grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Event, request),  // bytes offset in struct
    NULL,  // default value
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Event__request,  // size() function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__request,  // get_const(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__request,  // get(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Event__request,  // fetch(index, &value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Event__request,  // assign(index, value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(grasp_planner_msgs__srv__PlanGrasp_Event, response),  // bytes offset in struct
    NULL,  // default value
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__size_function__PlanGrasp_Event__response,  // size() function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_const_function__PlanGrasp_Event__response,  // get_const(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__get_function__PlanGrasp_Event__response,  // get(index) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__fetch_function__PlanGrasp_Event__response,  // fetch(index, &value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__assign_function__PlanGrasp_Event__response,  // assign(index, value) function pointer
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__resize_function__PlanGrasp_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_members = {
  "grasp_planner_msgs__srv",  // message namespace
  "PlanGrasp_Event",  // message name
  3,  // number of fields
  sizeof(grasp_planner_msgs__srv__PlanGrasp_Event),
  false,  // has_any_key_member_
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_member_array,  // message members
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_type_support_handle = {
  0,
  &grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_members,
  get_message_typesupport_handle_function,
  &grasp_planner_msgs__srv__PlanGrasp_Event__get_type_hash,
  &grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description,
  &grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_grasp_planner_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Event)() {
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Request)();
  grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Response)();
  if (!grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_type_support_handle.typesupport_identifier) {
    grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "grasp_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_members = {
  "grasp_planner_msgs__srv",  // service namespace
  "PlanGrasp",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle,
  NULL,  // response message
  // grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle
  NULL  // event_message
  // grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle
};


static rosidl_service_type_support_t grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_type_support_handle = {
  0,
  &grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_members,
  get_service_typesupport_handle_function,
  &grasp_planner_msgs__srv__PlanGrasp_Request__rosidl_typesupport_introspection_c__PlanGrasp_Request_message_type_support_handle,
  &grasp_planner_msgs__srv__PlanGrasp_Response__rosidl_typesupport_introspection_c__PlanGrasp_Response_message_type_support_handle,
  &grasp_planner_msgs__srv__PlanGrasp_Event__rosidl_typesupport_introspection_c__PlanGrasp_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    grasp_planner_msgs,
    srv,
    PlanGrasp
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    grasp_planner_msgs,
    srv,
    PlanGrasp
  ),
  &grasp_planner_msgs__srv__PlanGrasp__get_type_hash,
  &grasp_planner_msgs__srv__PlanGrasp__get_type_description,
  &grasp_planner_msgs__srv__PlanGrasp__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_grasp_planner_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp)(void) {
  if (!grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_type_support_handle.typesupport_identifier) {
    grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, grasp_planner_msgs, srv, PlanGrasp_Event)()->data;
  }

  return &grasp_planner_msgs__srv__detail__plan_grasp__rosidl_typesupport_introspection_c__PlanGrasp_service_type_support_handle;
}
