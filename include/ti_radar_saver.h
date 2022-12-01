#ifndef TI_RADAR_SAVER_H
#define TI_RADAR_SAVER_H

/**********************************

    Created on : 01 December 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <ti_mmwave_rospkg/RadarScan.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class TiRadarSaver
{
public:
  TiRadarSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~TiRadarSaver(){}

private:
  void tiRadarCallback(const ti_mmwave_rospkg::RadarScan::ConstPtr& ti_radar_msg);
  ros::Subscriber ti_radar_sub;
  std::string _ti_radar_topic, _output_path;
  std::ofstream MyFile;
};

#endif

