#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rx20_16_tf_broadcaster");

  ros::NodeHandle nh;
  tf2_ros::TransformBroadcaster broadcaster;

  std::string base_frame_id = "base_link";
  std::string odom_frame_id = "odom";


  double x = 0.0;    // Robot's x position
  double y = 0.0;    // Robot's y position
  double theta = 0.0;    // Robot's orientation angle

  ros::Rate rate(10);  // TF broadcast rate (10 Hz)

  while (ros::ok())
  {
    geometry_msgs::TransformStamped transformStamped;
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = odom_frame_id;
    transformStamped.child_frame_id = base_frame_id;
    transformStamped.transform.translation.x = x;
    transformStamped.transform.translation.y = y;
    transformStamped.transform.translation.z = 0.0;
    tf2::Quaternion q;
    q.setRPY(0, 0, theta);
    transformStamped.transform.rotation.x = q.x();
    transformStamped.transform.rotation.y = q.y();
    transformStamped.transform.rotation.z = q.z();
    transformStamped.transform.rotation.w = q.w();

    broadcaster.sendTransform(transformStamped);

    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

