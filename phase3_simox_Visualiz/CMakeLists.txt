cmake_minimum_required(VERSION 3.10)
project(SimoxViewer)

find_package(Simox REQUIRED)
find_package(SoQt REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)

include_directories(${Simox_INCLUDE_DIRS})
include_directories(${SoQt_INCLUDE_DIRS})

add_executable(simox_viewer simox_viewer.cpp)

target_link_libraries(simox_viewer
    ${Simox_LIBRARIES}
    SoQt::SoQt
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::OpenGL
)

install(TARGETS simox_viewer DESTINATION lib/${PROJECT_NAME})
