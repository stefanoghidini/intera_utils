cmake_minimum_required(VERSION 2.8.3)
project(intera_utils)
set(CMAKE_BUILD_TYPE Debug)
add_definitions( -std=c++11 -funroll-loops -O3 )

find_package(catkin REQUIRED COMPONENTS
  roscpp
  intera_core_msgs
  geometry_msgs
  ros_myo
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES
 CATKIN_DEPENDS roscpp intera_core_msgs geometry_msgs ros_myo
 DEPENDS 
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(ft_topic_convert src/intera_utils/ft_topic_convert.cpp)
target_link_libraries(ft_topic_convert
  ${catkin_LIBRARIES}
)

add_executable(myo_control src/${PROJECT_NAME}/myo_control.cpp)
target_link_libraries(myo_control
  ${catkin_LIBRARIES}
)