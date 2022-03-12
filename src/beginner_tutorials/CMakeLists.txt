cmake_minimum_required(VERSION 3.0.2)
project(beginner_tutorials)
# project (node_cam)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
   cv_bridge
   image_geometry
   roscpp
   rospy
   std_msgs
   message_generation
   genmsg
)
find_package( OpenCV REQUIRED )

## Declare ROS messages and services
add_message_files(FILES mess.msg)
##add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(node_cam src/node_cam.cpp)
target_link_libraries(node_cam ${catkin_LIBRARIES} ${OpenCV_LIBS})
# add_dependencies(node_cam beginner_tutorials_generate_messages_cpp)

add_executable(node_pc src/node_pc.cpp)
target_link_libraries(node_pc ${catkin_LIBRARIES})
# add_dependencies(node_pc beginner_tutorials_generate_messages_cpp)

add_executable(node_motor src/node_motor.cpp)
target_link_libraries(node_motor ${catkin_LIBRARIES})
# add_dependencies(node_motor beginner_tutorials_generate_messages_cpp)
