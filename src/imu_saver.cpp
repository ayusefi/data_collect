/**********************************

    Created on : 25 November 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "imu_saver.h"

ImuSaver::ImuSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("imu_topic", _imu_topic, "");
  ROS_INFO("imu_topic: %s", _imu_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  MyFile.open(_output_path + "Imu.txt");

  imu_sub = node.subscribe(_imu_topic, 1, &ImuSaver::imuCallback, this);
}

void ImuSaver::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
  std::stringstream ss;
  ss << imu_msg->header.stamp.sec << "." << imu_msg->header.stamp.nsec;
  
  MyFile << std::setprecision(10) << ss.str() <<','<< imu_msg->linear_acceleration.x <<','<<imu_msg->linear_acceleration.y<<','<<imu_msg->linear_acceleration.z<<','<<
            imu_msg->angular_velocity.x<<','<<imu_msg->angular_velocity.y<<','<<imu_msg->angular_velocity.z<<','<<
            imu_msg->orientation.x<<','<<imu_msg->orientation.y<<','<<imu_msg->orientation.z<<','<<imu_msg->orientation.w<<'\n';
}
