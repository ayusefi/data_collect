#ifndef IMU_SAVER_H
#define IMU_SAVER_H

/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class ImuSaver
{
public:
  ImuSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~ImuSaver(){}

private:
  void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg);
  ros::Subscriber imu_sub;
  std::string _imu_topic, _output_path;
  std::ofstream MyFile;
};

#endif

