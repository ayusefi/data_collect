#ifndef FLOAT32STAMPED_SAVER_H
#define FLOAT32STAMPED_SAVER_H

/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <marti_common_msgs/Float32Stamped.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class Float32stampedSaver
{
public:
  Float32stampedSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~Float32stampedSaver(){}

private:
  void float32stampedCallback(const marti_common_msgs::Float32Stamped::ConstPtr& float32stamped_msg);
  ros::Subscriber float32stamped_sub;
  std::string _float32stamped_topic, _output_path;
  std::ofstream MyFile;
};

#endif

