# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_grasp_planner_service_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED grasp_planner_service_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(grasp_planner_service_FOUND FALSE)
  elseif(NOT grasp_planner_service_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(grasp_planner_service_FOUND FALSE)
  endif()
  return()
endif()
set(_grasp_planner_service_CONFIG_INCLUDED TRUE)

# output package information
if(NOT grasp_planner_service_FIND_QUIETLY)
  message(STATUS "Found grasp_planner_service: 0.0.0 (${grasp_planner_service_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'grasp_planner_service' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT grasp_planner_service_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(grasp_planner_service_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${grasp_planner_service_DIR}/${_extra}")
endforeach()
