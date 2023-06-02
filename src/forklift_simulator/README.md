## Forklift_Simulator
Simulated forklift &amp; sensors (2D&amp;3D Lidars + RGBD-camera) in warehouse environment



### Launch
- To test simulation of **forklift EXV_14**, run:
>roslaunch forklift_simulator forklift_simulation.launch\
rosrun forklift_simulator keyboard_control_forklift

- To **spawn the container**, run:
>roslaunch forklift_simulator container_simulation.launch\
rosrun forklift_simulator keyboard_control_container

- To **visualize** on rviz, run:
>roslaunch forklift_simulator visualize.launch
