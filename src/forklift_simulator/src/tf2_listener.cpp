#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "rx20_16_tf_listener");

  ros::NodeHandle node;

  ros::Publisher cmd_vel_pub = node.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(10.0);

  while (ros::ok()) {
    geometry_msgs::TransformStamped transformStamped;
    try {
      transformStamped = tfBuffer.lookupTransform("base_link", "odom", ros::Time(0));
    } catch (tf2::TransformException& ex) {
      ROS_WARN("%s", ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    geometry_msgs::Twist vel_msg;

    // Modify the code below based on your desired velocity calculation
    vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y,
                                    transformStamped.transform.translation.x);
    vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) +
                                  pow(transformStamped.transform.translation.y, 2));

    cmd_vel_pub.publish(vel_msg);

    rate.sleep();
  }

  return 0;
}
