#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/impl/utils.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <gazebo_msgs/ModelStates.h>

// Global variables to store the robot's position and velocity
double x = 0.0;
double y = 0.0;
double theta = 0.0;
double linear_vel = 0.0;
double angular_vel = 0.0;

// Callback function to update the robot's position and velocity
void modelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
  // Find the robot's index in the model states
  int robot_index = -1;
  for (size_t i = 0; i < msg->name.size(); ++i)
  {
    if (msg->name[i] == "RX20_16")
    {
      robot_index = i;
      break;
    }
  }

  if (robot_index != -1)
  {
    // Get the robot's position and orientation
    x = msg->pose[robot_index].position.x;
    y = msg->pose[robot_index].position.y;
    theta = tf::getYaw(msg->pose[robot_index].orientation);

    // Get the robot's linear and angular velocity
    linear_vel = msg->twist[robot_index].linear.x;
    angular_vel = msg->twist[robot_index].angular.z;
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "forklift_odometry_publisher");

  ros::NodeHandle nh;
  ros::Subscriber model_states_sub = nh.subscribe("RX20_16/gazebo/model_states", 10, modelStatesCallback);
  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 10);
  tf2_ros::TransformBroadcaster tf_broadcaster;

  ros::Rate rate(10);  // Odometry update rate (10 Hz)

  while (ros::ok())
  {
    // Create and populate the odometry message
    nav_msgs::Odometry odom;
    odom.header.stamp = ros::Time::now();
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";

    // Set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = tf2::toMsg(tf2::Quaternion(tf2::Vector3(0, 0, 1), theta));

    // Set the velocity
    odom.twist.twist.linear.x = linear_vel;
    odom.twist.twist.angular.z = angular_vel;

    // Publish the odometry message
    odom_pub.publish(odom);

    // Broadcast the odometry transform
    geometry_msgs::TransformStamped transformStamped;
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "odom";
    transformStamped.child_frame_id = "base_link";
    transformStamped.transform.translation.x = x;
    transformStamped.transform.translation.y = y;
    transformStamped.transform.translation.z = 0.0;
    transformStamped.transform.rotation = tf2::toMsg(tf2::Quaternion(tf2::Vector3(0, 0, 1), theta));
    tf_broadcaster.sendTransform(transformStamped);

    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
