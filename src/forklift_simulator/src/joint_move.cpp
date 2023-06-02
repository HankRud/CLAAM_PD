#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include "std_msgs/String.h"

class JointMove
{
public:
  JointMove()
  {
  
    ros::NodeHandle nh;
    cmd_vel_sub_ = nh.subscribe("/cmd_vel",20, &JointMove::cmdVelCallback, this);
    left_joint_pub = nh.advertise<std_msgs::Float64>("wheel_front_left_driving_joint_controller/command", 1000);
    right_joint_pub = nh.advertise<std_msgs::Float64>("wheel_front_right_driving_joint_controller/command", 1000);
    left_steer_pub = nh.advertise<std_msgs::Float64>("rear_left_steer_joint_controller/command", 1000);
    right_steer_pub = nh.advertise<std_msgs::Float64>("rear_right_steer_joint_controller/command", 1000);
  
  }

  void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg)
  {

    double linear_vel = msg->linear.x;
    double angular_vel = msg->angular.z;

    double rear_steering_angle = -angular_vel;


    double front_drive_velocity = linear_vel;

    std_msgs::Float64 front_drive_msg;
    front_drive_msg.data = front_drive_velocity;

    std_msgs::Float64 rear_steering_msg;
    rear_steering_msg.data = rear_steering_angle;

    // Publish rear wheel steering angle and front wheel driving velocity
    left_joint_pub.publish(front_drive_msg);
    right_joint_pub.publish(front_drive_msg);
    left_steer_pub.publish(rear_steering_msg);
    right_steer_pub.publish(rear_steering_msg);
  }

private:
  ros::Subscriber cmd_vel_sub_;
  ros::Publisher left_joint_pub;
  ros::Publisher right_joint_pub;
  ros::Publisher left_steer_pub;
  ros::Publisher right_steer_pub;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ackerman_driver");
  JointMove controller;
  ros::spin();
  return 0;
}
