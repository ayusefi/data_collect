#ifndef ODOMETRY_SAVER_H
#define ODOMETRY_SAVER_H

/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class OdometrySaver
{
public:
  OdometrySaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~OdometrySaver(){}

private:
  void odometryCallback(const nav_msgs::Odometry::ConstPtr& odometry_msg);
  ros::Subscriber odometry_sub;
  std::string _odometry_topic, _output_path;
};

#endif

