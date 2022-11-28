#ifndef FLOAT64_SAVER_H
#define FLOAT64_SAVER_H

/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class Float64Saver
{
public:
  Float64Saver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~Float64Saver(){}

private:
  void float64Callback(const std_msgs::Float64::ConstPtr& float64_msg);
  ros::Subscriber float64_sub;
  std::string _float64_topic, _output_path;
  std::ofstream MyFile;
};

#endif

