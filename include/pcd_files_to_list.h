#ifndef PCD_FILES_TO_LIST_H
#define PCD_FILES_TO_LIST_H

/**********************************

    Created on : 06 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <chrono>

class PcdFilesToList
{
public:
  PcdFilesToList(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~PcdFilesToList(){}

  void pcdFilesToList();

private:
  std::string _directory_path;
};

#endif

