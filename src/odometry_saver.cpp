/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "odometry_saver.h"

OdometrySaver::OdometrySaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("odometry_topic", _odometry_topic, "");
  ROS_INFO("odometry_topic: %s", _odometry_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  MyFile.open(_output_path + "odom.txt");

  odometry_sub = node.subscribe(_odometry_topic, 1, &OdometrySaver::odometryCallback, this);
}

void OdometrySaver::odometryCallback(const nav_msgs::Odometry::ConstPtr& odometry_msg)
{
  std::stringstream ss;
  ss << odometry_msg->header.stamp.sec << "." << odometry_msg->header.stamp.nsec;

  MyFile << std::setprecision(10) << ss.str() << ',' <<
            odometry_msg->pose.pose.position.x <<','<<odometry_msg->pose.pose.position.y<<','<<odometry_msg->pose.pose.position.z<<','<<
            odometry_msg->pose.pose.orientation.x<<','<<odometry_msg->pose.pose.orientation.y<<','<<odometry_msg->pose.pose.orientation.z<<','<<
            odometry_msg->pose.pose.orientation.w<<'\n';
}
