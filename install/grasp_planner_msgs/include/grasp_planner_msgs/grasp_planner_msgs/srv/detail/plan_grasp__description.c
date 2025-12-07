// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

#include "grasp_planner_msgs/srv/detail/plan_grasp__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x04, 0x09, 0x60, 0xe7, 0x46, 0x86, 0x5a, 0x3f,
      0x8d, 0x91, 0xb0, 0x26, 0xca, 0xf8, 0xc3, 0xf7,
      0x67, 0x9e, 0xd8, 0xee, 0x8a, 0x78, 0x31, 0x71,
      0x4a, 0x64, 0xba, 0x12, 0xdc, 0x79, 0xa8, 0x96,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x37, 0xc4, 0x8e, 0x3d, 0x6e, 0xaf, 0x0e, 0xda,
      0xd1, 0x5a, 0xea, 0x61, 0x7a, 0x65, 0xe5, 0x8e,
      0xfa, 0xeb, 0x08, 0x10, 0x55, 0x25, 0x3a, 0x25,
      0x0a, 0x2e, 0x76, 0x1c, 0xef, 0x8d, 0x70, 0x2f,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x80, 0x14, 0x7f, 0x7d, 0xdd, 0x3e, 0xd8, 0xb2,
      0x0f, 0x34, 0xc5, 0xce, 0x10, 0xc3, 0x97, 0x38,
      0x43, 0x96, 0x4e, 0x99, 0xef, 0x29, 0x3b, 0x9a,
      0x61, 0xa4, 0xf5, 0x15, 0xe3, 0xea, 0xfa, 0x87,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_grasp_planner_msgs
const rosidl_type_hash_t *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa1, 0x25, 0xe9, 0x50, 0x03, 0x03, 0x81, 0x5a,
      0x44, 0x0c, 0xdf, 0x60, 0x68, 0x6d, 0x90, 0x61,
      0xa9, 0x3b, 0xfc, 0x09, 0xb2, 0x75, 0xcf, 0x1e,
      0xa3, 0x0a, 0x9a, 0x47, 0x59, 0xf2, 0xa2, 0xc8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "geometry_msgs/msg/detail/point__functions.h"
#include "geometry_msgs/msg/detail/pose__functions.h"
#include "geometry_msgs/msg/detail/quaternion__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Pose__EXPECTED_HASH = {1, {
    0xd5, 0x01, 0x95, 0x4e, 0x94, 0x76, 0xce, 0xa2,
    0x99, 0x69, 0x84, 0xe8, 0x12, 0x05, 0x4b, 0x68,
    0x02, 0x6a, 0xe0, 0xbf, 0xae, 0x78, 0x9d, 0x9a,
    0x10, 0xb2, 0x3d, 0xaf, 0x35, 0xcc, 0x90, 0xfa,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Quaternion__EXPECTED_HASH = {1, {
    0x8a, 0x76, 0x5f, 0x66, 0x77, 0x8c, 0x8f, 0xf7,
    0xc8, 0xab, 0x94, 0xaf, 0xcc, 0x59, 0x0a, 0x2e,
    0xd5, 0x32, 0x5a, 0x1d, 0x9a, 0x07, 0x6f, 0xff,
    0xf3, 0x8f, 0xbc, 0xe3, 0x6f, 0x45, 0x86, 0x84,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char grasp_planner_msgs__srv__PlanGrasp__TYPE_NAME[] = "grasp_planner_msgs/srv/PlanGrasp";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char geometry_msgs__msg__Pose__TYPE_NAME[] = "geometry_msgs/msg/Pose";
static char geometry_msgs__msg__Quaternion__TYPE_NAME[] = "geometry_msgs/msg/Quaternion";
static char grasp_planner_msgs__srv__PlanGrasp_Event__TYPE_NAME[] = "grasp_planner_msgs/srv/PlanGrasp_Event";
static char grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME[] = "grasp_planner_msgs/srv/PlanGrasp_Request";
static char grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME[] = "grasp_planner_msgs/srv/PlanGrasp_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__request_message[] = "request_message";
static char grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__response_message[] = "response_message";
static char grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field grasp_planner_msgs__srv__PlanGrasp__FIELDS[] = {
  {
    {grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {grasp_planner_msgs__srv__PlanGrasp_Event__TYPE_NAME, 38, 38},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription grasp_planner_msgs__srv__PlanGrasp__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Event__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {grasp_planner_msgs__srv__PlanGrasp__TYPE_NAME, 32, 32},
      {grasp_planner_msgs__srv__PlanGrasp__FIELDS, 3, 3},
    },
    {grasp_planner_msgs__srv__PlanGrasp__REFERENCED_TYPE_DESCRIPTIONS, 8, 8},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Pose__EXPECTED_HASH, geometry_msgs__msg__Pose__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Pose__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[6].fields = grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[7].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__robot_model_path[] = "robot_model_path";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__object_model_path[] = "object_model_path";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__object_pose[] = "object_pose";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__end_effector_name[] = "end_effector_name";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__kinematic_chain_name[] = "kinematic_chain_name";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__preshape_name[] = "preshape_name";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__quality_threshold[] = "quality_threshold";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__timeout_ms[] = "timeout_ms";
static char grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__num_grasps_to_plan[] = "num_grasps_to_plan";

static rosidl_runtime_c__type_description__Field grasp_planner_msgs__srv__PlanGrasp_Request__FIELDS[] = {
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__robot_model_path, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__object_model_path, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__object_pose, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__end_effector_name, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__kinematic_chain_name, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__preshape_name, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__quality_threshold, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__timeout_ms, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__FIELD_NAME__num_grasps_to_plan, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription grasp_planner_msgs__srv__PlanGrasp_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
      {grasp_planner_msgs__srv__PlanGrasp_Request__FIELDS, 9, 9},
    },
    {grasp_planner_msgs__srv__PlanGrasp_Request__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Pose__EXPECTED_HASH, geometry_msgs__msg__Pose__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Pose__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__success[] = "success";
static char grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__error_message[] = "error_message";
static char grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__qualities[] = "qualities";
static char grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__grasp_poses[] = "grasp_poses";
static char grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__are_force_closure[] = "are_force_closure";

static rosidl_runtime_c__type_description__Field grasp_planner_msgs__srv__PlanGrasp_Response__FIELDS[] = {
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__error_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__qualities, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__grasp_poses, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__FIELD_NAME__are_force_closure, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription grasp_planner_msgs__srv__PlanGrasp_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
      {grasp_planner_msgs__srv__PlanGrasp_Response__FIELDS, 5, 5},
    },
    {grasp_planner_msgs__srv__PlanGrasp_Response__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Pose__EXPECTED_HASH, geometry_msgs__msg__Pose__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Pose__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__info[] = "info";
static char grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__request[] = "request";
static char grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field grasp_planner_msgs__srv__PlanGrasp_Event__FIELDS[] = {
  {
    {grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription grasp_planner_msgs__srv__PlanGrasp_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Pose__TYPE_NAME, 22, 22},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Quaternion__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {grasp_planner_msgs__srv__PlanGrasp_Event__TYPE_NAME, 38, 38},
      {grasp_planner_msgs__srv__PlanGrasp_Event__FIELDS, 3, 3},
    },
    {grasp_planner_msgs__srv__PlanGrasp_Event__REFERENCED_TYPE_DESCRIPTIONS, 7, 7},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Pose__EXPECTED_HASH, geometry_msgs__msg__Pose__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Pose__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Quaternion__EXPECTED_HASH, geometry_msgs__msg__Quaternion__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = geometry_msgs__msg__Quaternion__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[6].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# grasp_planner_service/srv/PlanGrasp.srv\n"
  "\n"
  "# Request\n"
  "string robot_model_path\n"
  "string object_model_path\n"
  "geometry_msgs/Pose object_pose  # ADDED: Object pose in the world\n"
  "string end_effector_name\n"
  "string kinematic_chain_name # ADDED: Kinematic chain for IK checks\n"
  "string preshape_name\n"
  "float32 quality_threshold\n"
  "int32 timeout_ms\n"
  "int32 num_grasps_to_plan      # ADDED: Number of grasps to find\n"
  "---\n"
  "# Response\n"
  "bool success\n"
  "string error_message          # ADDED: Descriptive error message\n"
  "\n"
  "# CHANGED: These are now arrays\n"
  "float32[] qualities\n"
  "geometry_msgs/Pose[] grasp_poses\n"
  "bool[] are_force_closure\n"
  "";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {grasp_planner_msgs__srv__PlanGrasp__TYPE_NAME, 32, 32},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 593, 593},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {grasp_planner_msgs__srv__PlanGrasp_Request__TYPE_NAME, 40, 40},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {grasp_planner_msgs__srv__PlanGrasp_Response__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
grasp_planner_msgs__srv__PlanGrasp_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {grasp_planner_msgs__srv__PlanGrasp_Event__TYPE_NAME, 38, 38},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[9];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 9, 9};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *grasp_planner_msgs__srv__PlanGrasp__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Pose__get_individual_type_description_source(NULL);
    sources[4] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    sources[5] = *grasp_planner_msgs__srv__PlanGrasp_Event__get_individual_type_description_source(NULL);
    sources[6] = *grasp_planner_msgs__srv__PlanGrasp_Request__get_individual_type_description_source(NULL);
    sources[7] = *grasp_planner_msgs__srv__PlanGrasp_Response__get_individual_type_description_source(NULL);
    sources[8] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *grasp_planner_msgs__srv__PlanGrasp_Request__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Pose__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *grasp_planner_msgs__srv__PlanGrasp_Response__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Pose__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
grasp_planner_msgs__srv__PlanGrasp_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[8];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 8, 8};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *grasp_planner_msgs__srv__PlanGrasp_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Pose__get_individual_type_description_source(NULL);
    sources[4] = *geometry_msgs__msg__Quaternion__get_individual_type_description_source(NULL);
    sources[5] = *grasp_planner_msgs__srv__PlanGrasp_Request__get_individual_type_description_source(NULL);
    sources[6] = *grasp_planner_msgs__srv__PlanGrasp_Response__get_individual_type_description_source(NULL);
    sources[7] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
