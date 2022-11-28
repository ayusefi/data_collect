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

  odometry_sub = node.subscribe(_odometry_topic, 1, &OdometrySaver::odometryCallback, this);
}

void OdometrySaver::odometryCallback(const nav_msgs::Odometry::ConstPtr& odometry_msg)
{
  std::stringstream ss;
  ss << odometry_msg->header.stamp.sec << "." << odometry_msg->header.stamp.nsec;
  std::ofstream MyFile(_output_path + ss.str() +".txt");
  MyFile << std::setprecision(10) << 
            odometry_msg->pose.pose.position.x <<','<<odometry_msg->pose.pose.position.y<<','<<odometry_msg->pose.pose.position.z<<','<<
            odometry_msg->pose.pose.orientation.x<<','<<odometry_msg->pose.pose.orientation.y<<','<<odometry_msg->pose.pose.orientation.z<<','<<
            odometry_msg->pose.pose.orientation.w;
  MyFile.close();
  // ROS_INFO("Odometry position x: [%f], y: [%f], z: [%f]", odometry_msg->pose.pose.position.x, odometry_msg->pose.pose.position.y, 
  //                                                         odometry_msg->pose.pose.position.z);
  // ROS_INFO("Odometry orientation x: [%f], y: [%f], z: [%f], w: [%f]", odometry_msg->pose.pose.orientation.x, odometry_msg->pose.pose.orientation.y, 
                                                                      // odometry_msg->pose.pose.orientation.z, odometry_msg->pose.pose.orientation.w);
}
