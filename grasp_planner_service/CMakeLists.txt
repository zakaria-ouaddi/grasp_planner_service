cmake_minimum_required(VERSION 3.8)
project(grasp_planner_service)
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(grasp_planner_msgs REQUIRED)

# Find Simox and its dependencies
find_package(Boost REQUIRED COMPONENTS program_options thread regex)
find_package(Eigen3 REQUIRED)
find_package(Simox REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME}
  src/grasp_planner_service.cpp
)

message(STATUS "Simox_INCLUDE_DIRS: ${Simox_INCLUDE_DIRS}")
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Simox_INCLUDE_DIRS}
)

message(STATUS "Simox_LIBRARIES: ${Simox_LIBRARIES}")
# Link dependencies
target_link_libraries(${PROJECT_NAME}
  ${Simox_LIBRARIES}
)

ament_target_dependencies(${PROJECT_NAME}
rclcpp
std_msgs
geometry_msgs
grasp_planner_msgs
)

add_executable(${PROJECT_NAME}_node src/grasp_planner_service_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME})

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
  geometry_msgs
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
