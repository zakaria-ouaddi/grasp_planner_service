// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from grasp_planner_msgs:srv/PlanGrasp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "grasp_planner_msgs/srv/plan_grasp.hpp"


#ifndef GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_HPP_
#define GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'object_pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Request __attribute__((deprecated))
#else
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Request __declspec(deprecated)
#endif

namespace grasp_planner_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlanGrasp_Request_
{
  using Type = PlanGrasp_Request_<ContainerAllocator>;

  explicit PlanGrasp_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : object_pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_model_path = "";
      this->object_model_path = "";
      this->end_effector_name = "";
      this->kinematic_chain_name = "";
      this->preshape_name = "";
      this->quality_threshold = 0.0f;
      this->timeout_ms = 0l;
      this->num_grasps_to_plan = 0l;
    }
  }

  explicit PlanGrasp_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_model_path(_alloc),
    object_model_path(_alloc),
    object_pose(_alloc, _init),
    end_effector_name(_alloc),
    kinematic_chain_name(_alloc),
    preshape_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_model_path = "";
      this->object_model_path = "";
      this->end_effector_name = "";
      this->kinematic_chain_name = "";
      this->preshape_name = "";
      this->quality_threshold = 0.0f;
      this->timeout_ms = 0l;
      this->num_grasps_to_plan = 0l;
    }
  }

  // field types and members
  using _robot_model_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_model_path_type robot_model_path;
  using _object_model_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _object_model_path_type object_model_path;
  using _object_pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _object_pose_type object_pose;
  using _end_effector_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _end_effector_name_type end_effector_name;
  using _kinematic_chain_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _kinematic_chain_name_type kinematic_chain_name;
  using _preshape_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _preshape_name_type preshape_name;
  using _quality_threshold_type =
    float;
  _quality_threshold_type quality_threshold;
  using _timeout_ms_type =
    int32_t;
  _timeout_ms_type timeout_ms;
  using _num_grasps_to_plan_type =
    int32_t;
  _num_grasps_to_plan_type num_grasps_to_plan;

  // setters for named parameter idiom
  Type & set__robot_model_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_model_path = _arg;
    return *this;
  }
  Type & set__object_model_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->object_model_path = _arg;
    return *this;
  }
  Type & set__object_pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->object_pose = _arg;
    return *this;
  }
  Type & set__end_effector_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->end_effector_name = _arg;
    return *this;
  }
  Type & set__kinematic_chain_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->kinematic_chain_name = _arg;
    return *this;
  }
  Type & set__preshape_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->preshape_name = _arg;
    return *this;
  }
  Type & set__quality_threshold(
    const float & _arg)
  {
    this->quality_threshold = _arg;
    return *this;
  }
  Type & set__timeout_ms(
    const int32_t & _arg)
  {
    this->timeout_ms = _arg;
    return *this;
  }
  Type & set__num_grasps_to_plan(
    const int32_t & _arg)
  {
    this->num_grasps_to_plan = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Request
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Request
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlanGrasp_Request_ & other) const
  {
    if (this->robot_model_path != other.robot_model_path) {
      return false;
    }
    if (this->object_model_path != other.object_model_path) {
      return false;
    }
    if (this->object_pose != other.object_pose) {
      return false;
    }
    if (this->end_effector_name != other.end_effector_name) {
      return false;
    }
    if (this->kinematic_chain_name != other.kinematic_chain_name) {
      return false;
    }
    if (this->preshape_name != other.preshape_name) {
      return false;
    }
    if (this->quality_threshold != other.quality_threshold) {
      return false;
    }
    if (this->timeout_ms != other.timeout_ms) {
      return false;
    }
    if (this->num_grasps_to_plan != other.num_grasps_to_plan) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlanGrasp_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlanGrasp_Request_

// alias to use template instance with default allocator
using PlanGrasp_Request =
  grasp_planner_msgs::srv::PlanGrasp_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace grasp_planner_msgs


// Include directives for member types
// Member 'grasp_poses'
// already included above
// #include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Response __attribute__((deprecated))
#else
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Response __declspec(deprecated)
#endif

namespace grasp_planner_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlanGrasp_Response_
{
  using Type = PlanGrasp_Response_<ContainerAllocator>;

  explicit PlanGrasp_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_message = "";
    }
  }

  explicit PlanGrasp_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : error_message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _error_message_type error_message;
  using _qualities_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _qualities_type qualities;
  using _grasp_poses_type =
    std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>>;
  _grasp_poses_type grasp_poses;
  using _are_force_closure_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _are_force_closure_type are_force_closure;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__error_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->error_message = _arg;
    return *this;
  }
  Type & set__qualities(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->qualities = _arg;
    return *this;
  }
  Type & set__grasp_poses(
    const std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>> & _arg)
  {
    this->grasp_poses = _arg;
    return *this;
  }
  Type & set__are_force_closure(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->are_force_closure = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Response
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Response
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlanGrasp_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_message != other.error_message) {
      return false;
    }
    if (this->qualities != other.qualities) {
      return false;
    }
    if (this->grasp_poses != other.grasp_poses) {
      return false;
    }
    if (this->are_force_closure != other.are_force_closure) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlanGrasp_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlanGrasp_Response_

// alias to use template instance with default allocator
using PlanGrasp_Response =
  grasp_planner_msgs::srv::PlanGrasp_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace grasp_planner_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Event __attribute__((deprecated))
#else
# define DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Event __declspec(deprecated)
#endif

namespace grasp_planner_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlanGrasp_Event_
{
  using Type = PlanGrasp_Event_<ContainerAllocator>;

  explicit PlanGrasp_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit PlanGrasp_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<grasp_planner_msgs::srv::PlanGrasp_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<grasp_planner_msgs::srv::PlanGrasp_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Event
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__grasp_planner_msgs__srv__PlanGrasp_Event
    std::shared_ptr<grasp_planner_msgs::srv::PlanGrasp_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlanGrasp_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlanGrasp_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlanGrasp_Event_

// alias to use template instance with default allocator
using PlanGrasp_Event =
  grasp_planner_msgs::srv::PlanGrasp_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace grasp_planner_msgs

namespace grasp_planner_msgs
{

namespace srv
{

struct PlanGrasp
{
  using Request = grasp_planner_msgs::srv::PlanGrasp_Request;
  using Response = grasp_planner_msgs::srv::PlanGrasp_Response;
  using Event = grasp_planner_msgs::srv::PlanGrasp_Event;
};

}  // namespace srv

}  // namespace grasp_planner_msgs

#endif  // GRASP_PLANNER_MSGS__SRV__DETAIL__PLAN_GRASP__STRUCT_HPP_
