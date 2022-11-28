#ifndef NAVSATFIX_SAVER_V1_H
#define NAVSATFIX_SAVER_V1_H

/**********************************

    Created on : 28 November 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class NavsatfixSaver
{
public:
  NavsatfixSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~NavsatfixSaver(){}

private:
  void navsatfixCallback(const sensor_msgs::NavSatFix::ConstPtr& navsatfix_msg);
  ros::Subscriber navsatfix_sub;
  std::string _navsatfix_topic, _output_path;
  std::ofstream MyFile;
};

#endif