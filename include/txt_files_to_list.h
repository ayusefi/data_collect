#ifndef TXT_FILE_TO_LIST_H
#define TXT_FILE_TO_LIST_H

/**********************************

    Created on : 06 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <chrono>

class TxtFileToList
{
public:
  TxtFileToList(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~TxtFileToList(){}

  void txtFileToList();

private:
  void timestampStrToRos(const std::string* timestamp_str, ros::Time* time);

  std::string _directory_path;
  XmlRpc::XmlRpcValue _variable_names;
};

#endif

