cmake_minimum_required(VERSION 3.0.2)
project(forklift_simulator)

find_package(catkin REQUIRED COMPONENTS rostime roscpp rospy rosconsole roslaunch nav_core gmapping tf tf2 tf2_ros costmap_2d  
teb_local_planner controller_manager genmsg geometry_msgs actionlib_msgs move_base_msgs ackermann_steering_controller)
roslaunch_add_file_check(launch)

include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

generate_messages(DEPENDENCIES actionlib_msgs)

catkin_package(
   LIBRARIES forklift_simulator
   CATKIN_DEPENDS roscpp rospy std_msgs
)


add_executable(test_node src/test.cpp)
target_link_libraries(test_node ${catkin_LIBRARIES})
install(TARGETS test_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(test_subs_node src/test_subs.cpp)
target_link_libraries(test_subs_node ${catkin_LIBRARIES})
install(TARGETS test_subs_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(keyboard_control_forklift src/keyboard_control_RX20_16.cpp)
target_link_libraries(keyboard_control_forklift ${catkin_LIBRARIES})
install(TARGETS keyboard_control_forklift
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}) 

add_executable(keyboard_control_container src/keyboard_control_container_door.cpp)
target_link_libraries(keyboard_control_container ${catkin_LIBRARIES})
install(TARGETS keyboard_control_container
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})   

add_executable(tf_broadcaster src/tf2_broadcaster.cpp)
add_executable(tf_listener src/tf2_listener.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES}) 
target_link_libraries(tf_listener ${catkin_LIBRARIES})

add_executable(move_to_pallet src/move_to_pallet.cpp)
target_link_libraries(move_to_pallet ${catkin_LIBRARIES})


add_executable(publishOdom src/publishOdom.cpp)
target_link_libraries(publishOdom ${catkin_LIBRARIES})

add_executable(forklift_base src/forklift_base.cpp)
target_link_libraries(forklift_base ${catkin_LIBRARIES})

add_executable(joint_move src/joint_move.cpp)
target_link_libraries(joint_move ${catkin_LIBRARIES})


# install(DIRECTORY launch
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)

# install(DIRECTORY worlds
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

catkin_install_python(PROGRAMS
  scripts/keyboard_control.py
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/scripts
)

install(FILES
  launch/forklift_sim.launch
  launch/visualize.launch
  launch/test.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)
