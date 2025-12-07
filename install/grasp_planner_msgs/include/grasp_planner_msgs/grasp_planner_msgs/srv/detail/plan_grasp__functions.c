// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice
#include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `robot_model_path`
// Member `object_model_path`
// Member `end_effector_name`
// Member `kinematic_chain_name`
// Member `preshape_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `object_pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
grasp_planner_msgs__srv__PlanGrasp_Request__init(grasp_planner_msgs__srv__PlanGrasp_Request * msg)
{
  if (!msg) {
    return false;
  }
  // robot_model_path
  if (!rosidl_runtime_c__String__init(&msg->robot_model_path)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // object_model_path
  if (!rosidl_runtime_c__String__init(&msg->object_model_path)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // object_pose
  if (!geometry_msgs__msg__Pose__init(&msg->object_pose)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // end_effector_name
  if (!rosidl_runtime_c__String__init(&msg->end_effector_name)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // kinematic_chain_name
  if (!rosidl_runtime_c__String__init(&msg->kinematic_chain_name)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // preshape_name
  if (!rosidl_runtime_c__String__init(&msg->preshape_name)) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
    return false;
  }
  // quality_threshold
  // timeout_ms
  // num_grasps_to_plan
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Request__fini(grasp_planner_msgs__srv__PlanGrasp_Request * msg)
{
  if (!msg) {
    return;
  }
  // robot_model_path
  rosidl_runtime_c__String__fini(&msg->robot_model_path);
  // object_model_path
  rosidl_runtime_c__String__fini(&msg->object_model_path);
  // object_pose
  geometry_msgs__msg__Pose__fini(&msg->object_pose);
  // end_effector_name
  rosidl_runtime_c__String__fini(&msg->end_effector_name);
  // kinematic_chain_name
  rosidl_runtime_c__String__fini(&msg->kinematic_chain_name);
  // preshape_name
  rosidl_runtime_c__String__fini(&msg->preshape_name);
  // quality_threshold
  // timeout_ms
  // num_grasps_to_plan
}

bool
grasp_planner_msgs__srv__PlanGrasp_Request__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Request * lhs, const grasp_planner_msgs__srv__PlanGrasp_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // robot_model_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_model_path), &(rhs->robot_model_path)))
  {
    return false;
  }
  // object_model_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->object_model_path), &(rhs->object_model_path)))
  {
    return false;
  }
  // object_pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->object_pose), &(rhs->object_pose)))
  {
    return false;
  }
  // end_effector_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->end_effector_name), &(rhs->end_effector_name)))
  {
    return false;
  }
  // kinematic_chain_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->kinematic_chain_name), &(rhs->kinematic_chain_name)))
  {
    return false;
  }
  // preshape_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->preshape_name), &(rhs->preshape_name)))
  {
    return false;
  }
  // quality_threshold
  if (lhs->quality_threshold != rhs->quality_threshold) {
    return false;
  }
  // timeout_ms
  if (lhs->timeout_ms != rhs->timeout_ms) {
    return false;
  }
  // num_grasps_to_plan
  if (lhs->num_grasps_to_plan != rhs->num_grasps_to_plan) {
    return false;
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Request__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Request * input,
  grasp_planner_msgs__srv__PlanGrasp_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // robot_model_path
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_model_path), &(output->robot_model_path)))
  {
    return false;
  }
  // object_model_path
  if (!rosidl_runtime_c__String__copy(
      &(input->object_model_path), &(output->object_model_path)))
  {
    return false;
  }
  // object_pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->object_pose), &(output->object_pose)))
  {
    return false;
  }
  // end_effector_name
  if (!rosidl_runtime_c__String__copy(
      &(input->end_effector_name), &(output->end_effector_name)))
  {
    return false;
  }
  // kinematic_chain_name
  if (!rosidl_runtime_c__String__copy(
      &(input->kinematic_chain_name), &(output->kinematic_chain_name)))
  {
    return false;
  }
  // preshape_name
  if (!rosidl_runtime_c__String__copy(
      &(input->preshape_name), &(output->preshape_name)))
  {
    return false;
  }
  // quality_threshold
  output->quality_threshold = input->quality_threshold;
  // timeout_ms
  output->timeout_ms = input->timeout_ms;
  // num_grasps_to_plan
  output->num_grasps_to_plan = input->num_grasps_to_plan;
  return true;
}

grasp_planner_msgs__srv__PlanGrasp_Request *
grasp_planner_msgs__srv__PlanGrasp_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Request * msg = (grasp_planner_msgs__srv__PlanGrasp_Request *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(grasp_planner_msgs__srv__PlanGrasp_Request));
  bool success = grasp_planner_msgs__srv__PlanGrasp_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
grasp_planner_msgs__srv__PlanGrasp_Request__destroy(grasp_planner_msgs__srv__PlanGrasp_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    grasp_planner_msgs__srv__PlanGrasp_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Request * data = NULL;

  if (size) {
    data = (grasp_planner_msgs__srv__PlanGrasp_Request *)allocator.zero_allocate(size, sizeof(grasp_planner_msgs__srv__PlanGrasp_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = grasp_planner_msgs__srv__PlanGrasp_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        grasp_planner_msgs__srv__PlanGrasp_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      grasp_planner_msgs__srv__PlanGrasp_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array = (grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(grasp_planner_msgs__srv__PlanGrasp_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    grasp_planner_msgs__srv__PlanGrasp_Request * data =
      (grasp_planner_msgs__srv__PlanGrasp_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!grasp_planner_msgs__srv__PlanGrasp_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          grasp_planner_msgs__srv__PlanGrasp_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `error_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `qualities`
// Member `are_force_closure`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `grasp_poses`
// already included above
// #include "geometry_msgs/msg/detail/pose__functions.h"

bool
grasp_planner_msgs__srv__PlanGrasp_Response__init(grasp_planner_msgs__srv__PlanGrasp_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_message
  if (!rosidl_runtime_c__String__init(&msg->error_message)) {
    grasp_planner_msgs__srv__PlanGrasp_Response__fini(msg);
    return false;
  }
  // qualities
  if (!rosidl_runtime_c__float__Sequence__init(&msg->qualities, 0)) {
    grasp_planner_msgs__srv__PlanGrasp_Response__fini(msg);
    return false;
  }
  // grasp_poses
  if (!geometry_msgs__msg__Pose__Sequence__init(&msg->grasp_poses, 0)) {
    grasp_planner_msgs__srv__PlanGrasp_Response__fini(msg);
    return false;
  }
  // are_force_closure
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->are_force_closure, 0)) {
    grasp_planner_msgs__srv__PlanGrasp_Response__fini(msg);
    return false;
  }
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Response__fini(grasp_planner_msgs__srv__PlanGrasp_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_message
  rosidl_runtime_c__String__fini(&msg->error_message);
  // qualities
  rosidl_runtime_c__float__Sequence__fini(&msg->qualities);
  // grasp_poses
  geometry_msgs__msg__Pose__Sequence__fini(&msg->grasp_poses);
  // are_force_closure
  rosidl_runtime_c__boolean__Sequence__fini(&msg->are_force_closure);
}

bool
grasp_planner_msgs__srv__PlanGrasp_Response__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Response * lhs, const grasp_planner_msgs__srv__PlanGrasp_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // error_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->error_message), &(rhs->error_message)))
  {
    return false;
  }
  // qualities
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->qualities), &(rhs->qualities)))
  {
    return false;
  }
  // grasp_poses
  if (!geometry_msgs__msg__Pose__Sequence__are_equal(
      &(lhs->grasp_poses), &(rhs->grasp_poses)))
  {
    return false;
  }
  // are_force_closure
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->are_force_closure), &(rhs->are_force_closure)))
  {
    return false;
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Response__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Response * input,
  grasp_planner_msgs__srv__PlanGrasp_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_message
  if (!rosidl_runtime_c__String__copy(
      &(input->error_message), &(output->error_message)))
  {
    return false;
  }
  // qualities
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->qualities), &(output->qualities)))
  {
    return false;
  }
  // grasp_poses
  if (!geometry_msgs__msg__Pose__Sequence__copy(
      &(input->grasp_poses), &(output->grasp_poses)))
  {
    return false;
  }
  // are_force_closure
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->are_force_closure), &(output->are_force_closure)))
  {
    return false;
  }
  return true;
}

grasp_planner_msgs__srv__PlanGrasp_Response *
grasp_planner_msgs__srv__PlanGrasp_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Response * msg = (grasp_planner_msgs__srv__PlanGrasp_Response *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(grasp_planner_msgs__srv__PlanGrasp_Response));
  bool success = grasp_planner_msgs__srv__PlanGrasp_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
grasp_planner_msgs__srv__PlanGrasp_Response__destroy(grasp_planner_msgs__srv__PlanGrasp_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    grasp_planner_msgs__srv__PlanGrasp_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Response * data = NULL;

  if (size) {
    data = (grasp_planner_msgs__srv__PlanGrasp_Response *)allocator.zero_allocate(size, sizeof(grasp_planner_msgs__srv__PlanGrasp_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = grasp_planner_msgs__srv__PlanGrasp_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        grasp_planner_msgs__srv__PlanGrasp_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      grasp_planner_msgs__srv__PlanGrasp_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array = (grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(grasp_planner_msgs__srv__PlanGrasp_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    grasp_planner_msgs__srv__PlanGrasp_Response * data =
      (grasp_planner_msgs__srv__PlanGrasp_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!grasp_planner_msgs__srv__PlanGrasp_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          grasp_planner_msgs__srv__PlanGrasp_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"

bool
grasp_planner_msgs__srv__PlanGrasp_Event__init(grasp_planner_msgs__srv__PlanGrasp_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    grasp_planner_msgs__srv__PlanGrasp_Event__fini(msg);
    return false;
  }
  // request
  if (!grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init(&msg->request, 0)) {
    grasp_planner_msgs__srv__PlanGrasp_Event__fini(msg);
    return false;
  }
  // response
  if (!grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init(&msg->response, 0)) {
    grasp_planner_msgs__srv__PlanGrasp_Event__fini(msg);
    return false;
  }
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Event__fini(grasp_planner_msgs__srv__PlanGrasp_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini(&msg->request);
  // response
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini(&msg->response);
}

bool
grasp_planner_msgs__srv__PlanGrasp_Event__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Event * lhs, const grasp_planner_msgs__srv__PlanGrasp_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Event__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Event * input,
  grasp_planner_msgs__srv__PlanGrasp_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

grasp_planner_msgs__srv__PlanGrasp_Event *
grasp_planner_msgs__srv__PlanGrasp_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Event * msg = (grasp_planner_msgs__srv__PlanGrasp_Event *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(grasp_planner_msgs__srv__PlanGrasp_Event));
  bool success = grasp_planner_msgs__srv__PlanGrasp_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
grasp_planner_msgs__srv__PlanGrasp_Event__destroy(grasp_planner_msgs__srv__PlanGrasp_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    grasp_planner_msgs__srv__PlanGrasp_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Event * data = NULL;

  if (size) {
    data = (grasp_planner_msgs__srv__PlanGrasp_Event *)allocator.zero_allocate(size, sizeof(grasp_planner_msgs__srv__PlanGrasp_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = grasp_planner_msgs__srv__PlanGrasp_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        grasp_planner_msgs__srv__PlanGrasp_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      grasp_planner_msgs__srv__PlanGrasp_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

grasp_planner_msgs__srv__PlanGrasp_Event__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array = (grasp_planner_msgs__srv__PlanGrasp_Event__Sequence *)allocator.allocate(sizeof(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(grasp_planner_msgs__srv__PlanGrasp_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    grasp_planner_msgs__srv__PlanGrasp_Event * data =
      (grasp_planner_msgs__srv__PlanGrasp_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!grasp_planner_msgs__srv__PlanGrasp_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          grasp_planner_msgs__srv__PlanGrasp_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!grasp_planner_msgs__srv__PlanGrasp_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
