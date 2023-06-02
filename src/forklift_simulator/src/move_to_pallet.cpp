#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>



typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


double pallet_x = 0.0;
double pallet_y = 0.0;
double pallet_theta = 0.0;


void palletPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
 
  pallet_x = msg->pose.position.x;
  pallet_y = msg->pose.position.y;
  pallet_theta = msg->pose.position.z;
}




int main(int argc, char** argv)
{
  ros::init(argc, argv, "forklift_pallet_planner");

  ros::NodeHandle nh;
  ros::Subscriber pallet_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("/pd_pallet_pose", 10, palletPoseCallback);
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  MoveBaseClient ac("/move_base", true);

  ROS_INFO("Waiting for the move_base action server...");
  ac.waitForServer(ros::Duration(5));
  ROS_INFO("Connected to move_base action server");

  


  ros::Rate rate(10);  

  while (ros::ok())
  {
    if (pallet_x > 0.01 && pallet_y > 0.00)
    {
      // Create a move_base goal to reach the pallet
      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "map";  
      goal.target_pose.header.stamp = ros::Time::now();

      // Set the goal position and orientation based on the pallet pose
      goal.target_pose.pose.position.x = pallet_x;
      goal.target_pose.pose.position.y = pallet_y;
      goal.target_pose.pose.orientation.z = sin(pallet_theta / 2);
      goal.target_pose.pose.orientation.w = cos(pallet_theta / 2);

      // Send the goal to the move_base action server
      ROS_INFO("Sending goal to reach the pallet...");
      ac.sendGoal(goal);

      // Wait for the goal to be reached
      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        ROS_INFO("Robot reached the pallet!");

      }
      else
      {
        ROS_WARN("Failed to reach the pallet...");
      }

      // Reset the pallet pose
      pallet_x = 0.0;
      pallet_y = 0.0;
    }

    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
