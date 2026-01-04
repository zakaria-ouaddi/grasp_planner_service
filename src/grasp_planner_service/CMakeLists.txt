cmake_minimum_required(VERSION 3.8)
project(grasp_planner_service)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ROS 2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(grasp_planner_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)

find_package(rosidl_runtime_cpp REQUIRED)
find_package(eigen3_cmake_module REQUIRED)

# Find Simox and its core dependencies
find_package(Boost REQUIRED COMPONENTS program_options thread regex system filesystem)
find_package(Eigen3 REQUIRED)
find_package(Simox REQUIRED COMPONENTS VirtualRobot GraspStudio)  # Explicitly request Simox components

# Include directories
include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${Simox_INCLUDE_DIRS}
  
)

# Library target
add_library(${PROJECT_NAME}
  src/grasp_planner_service.cpp
)

# Link Simox and ROS 2 dependencies
target_link_libraries(${PROJECT_NAME}
  ${Simox_LIBRARIES}
  ${Boost_LIBRARIES}
  Eigen3::Eigen
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
  geometry_msgs
  grasp_planner_msgs
  visualization_msgs
  tf2_ros
  tf2_eigen
  rosidl_runtime_cpp
)

# Executable
add_executable(${PROJECT_NAME}_node 
  src/grasp_planner_service_node.cpp
)

add_executable(test_grasp_planner src/test_grasp_planner.cpp)
target_link_libraries(test_grasp_planner ${PROJECT_NAME})
ament_target_dependencies(test_grasp_planner
  rclcpp
  grasp_planner_msgs
  geometry_msgs
  rosidl_runtime_cpp
)


target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}
)

# Install targets
install(TARGETS
  ${PROJECT_NAME}
  ${PROJECT_NAME}_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
install(TARGETS test_grasp_planner
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

ament_export_dependencies(
  rclcpp
  std_msgs
  geometry_msgs
  visualization_msgs
  tf2_ros
  tf2_eigen
  grasp_planner_msgs
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  
  ament_add_gtest(test_conversions test/test_conversions.cpp)
  target_link_libraries(test_conversions 
    ${Simox_LIBRARIES}
    Eigen3::Eigen
    ${PROJECT_NAME} # Link to the library we defined above
  )
  ament_target_dependencies(test_conversions 
    rclcpp 
    geometry_msgs
  )

  ament_add_gtest(test_service_logic test/test_service_logic.cpp)
  target_link_libraries(test_service_logic 
    ${Simox_LIBRARIES}
    Eigen3::Eigen
    ${PROJECT_NAME} 
  )
  ament_target_dependencies(test_service_logic rclcpp grasp_planner_msgs)

endif()

ament_package()
