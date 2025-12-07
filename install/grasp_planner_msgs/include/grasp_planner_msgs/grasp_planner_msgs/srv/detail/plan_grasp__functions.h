// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "grasp_planner_msgs/srv/plan_grasp.h"


#ifndef GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__FUNCTIONS_H_
#define GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "grasp_planner_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "grasp_planner_msgs/srv/detail/plan_grasp__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/PlanGrasp message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * grasp_planner_msgs__srv__PlanGrasp_Request
 * )) before or use
 * grasp_planner_msgs__srv__PlanGrasp_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__init(grasp_planner_msgs__srv__PlanGrasp_Request * msg);

/// Finalize srv/PlanGrasp message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Request__fini(grasp_planner_msgs__srv__PlanGrasp_Request * msg);

/// Create srv/PlanGrasp message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Request *
grasp_planner_msgs__srv__PlanGrasp_Request__create(void);

/// Destroy srv/PlanGrasp message.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Request__destroy(grasp_planner_msgs__srv__PlanGrasp_Request * msg);

/// Check for srv/PlanGrasp message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Request * lhs, const grasp_planner_msgs__srv__PlanGrasp_Request * rhs);

/// Copy a srv/PlanGrasp message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Request * input,
  grasp_planner_msgs__srv__PlanGrasp_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the number of elements and calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array, size_t size);

/// Finalize array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array);

/// Create array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the array and calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__create(size_t size);

/// Destroy array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * array);

/// Check for srv/PlanGrasp message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * rhs);

/// Copy an array of srv/PlanGrasp messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Request__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Request__Sequence * output);

/// Initialize srv/PlanGrasp message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * grasp_planner_msgs__srv__PlanGrasp_Response
 * )) before or use
 * grasp_planner_msgs__srv__PlanGrasp_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__init(grasp_planner_msgs__srv__PlanGrasp_Response * msg);

/// Finalize srv/PlanGrasp message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Response__fini(grasp_planner_msgs__srv__PlanGrasp_Response * msg);

/// Create srv/PlanGrasp message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Response *
grasp_planner_msgs__srv__PlanGrasp_Response__create(void);

/// Destroy srv/PlanGrasp message.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Response__destroy(grasp_planner_msgs__srv__PlanGrasp_Response * msg);

/// Check for srv/PlanGrasp message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Response * lhs, const grasp_planner_msgs__srv__PlanGrasp_Response * rhs);

/// Copy a srv/PlanGrasp message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Response * input,
  grasp_planner_msgs__srv__PlanGrasp_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the number of elements and calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array, size_t size);

/// Finalize array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array);

/// Create array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the array and calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__create(size_t size);

/// Destroy array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * array);

/// Check for srv/PlanGrasp message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * rhs);

/// Copy an array of srv/PlanGrasp messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Response__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Response__Sequence * output);

/// Initialize srv/PlanGrasp message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * grasp_planner_msgs__srv__PlanGrasp_Event
 * )) before or use
 * grasp_planner_msgs__srv__PlanGrasp_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__init(grasp_planner_msgs__srv__PlanGrasp_Event * msg);

/// Finalize srv/PlanGrasp message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Event__fini(grasp_planner_msgs__srv__PlanGrasp_Event * msg);

/// Create srv/PlanGrasp message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Event *
grasp_planner_msgs__srv__PlanGrasp_Event__create(void);

/// Destroy srv/PlanGrasp message.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Event__destroy(grasp_planner_msgs__srv__PlanGrasp_Event * msg);

/// Check for srv/PlanGrasp message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Event * lhs, const grasp_planner_msgs__srv__PlanGrasp_Event * rhs);

/// Copy a srv/PlanGrasp message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Event * input,
  grasp_planner_msgs__srv__PlanGrasp_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the number of elements and calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__init(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array, size_t size);

/// Finalize array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__fini(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array);

/// Create array of srv/PlanGrasp messages.
/**
 * It allocates the memory for the array and calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__create(size_t size);

/// Destroy array of srv/PlanGrasp messages.
/**
 * It calls
 * grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
void
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__destroy(grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * array);

/// Check for srv/PlanGrasp message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__are_equal(const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * lhs, const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * rhs);

/// Copy an array of srv/PlanGrasp messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
bool
grasp_planner_msgs__srv__PlanGrasp_Event__Sequence__copy(
  const grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * input,
  grasp_planner_msgs__srv__PlanGrasp_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__FUNCTIONS_H_
