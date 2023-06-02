# CLAAM_PD- Counterbalanced Loader Autonomous Ackerman Motion and Pallet Detection 
 An integration of :
 -RX20_16 robot and multi_pallet_detection from https://github.com/cuongng313/auto_forklift_pallet_detection
 -ROS navigation https://github.com/ros-planning/navigation
 -ackerman_steering_controller https://github.com/ros-controls/ros_controllers
 -https://github.com/rst-tu-dortmund/teb_local_planner


# INSTALL
 This integration provides the basis for autonomous forklift navigation and pallet-based goal setting.
 
 add realsense gazebo library to your workspace
 
 git clone https://github.com/pal-robotics/realsense_gazebo_plugin.git
 
 Install dependencies
 
 rosdep install

 git clone https://github.com/pal-robotics/realsense_gazebo_plugin.git

 build your workspace with catkin_make


# SOURCE
 source /opt/ros/noetic/setup.bash
 source source devel/setup.bash
 export GAZEBO_MODEL_PATH=$HOME/CLAAM_PD/src/forklift_simulator/models

# LAUNCH

roslaunch simall.launch



