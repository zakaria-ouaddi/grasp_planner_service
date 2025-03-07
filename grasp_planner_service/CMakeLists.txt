cmake_minimum_required(VERSION 3.8)
project(grasp_planner_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(grasp_planner_msgs REQUIRED)

find_package(Boost REQUIRED COMPONENTS program_options thread regex)
find_package(Eigen3 REQUIRED)
find_package(Simox REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME}
  src/grasp_planner_service.cpp
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  grasp_planner_msgs
)

add_executable(${PROJECT_NAME}_node src/grasp_planner_service_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME})
ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  grasp_planner_msgs
)

# Install
install(TARGETS
  ${PROJECT_NAME}
  ${PROJECT_NAME}_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

ament_package()
