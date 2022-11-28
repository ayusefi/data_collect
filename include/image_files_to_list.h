#ifndef IMAGE_FILES_TO_LIST_H
#define IMAGE_FILES_TO_LIST_H

/**********************************

    Created on : 06 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <chrono>

class ImageFilesToList
{
public:
  ImageFilesToList(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~ImageFilesToList(){}

  void imageFilesToList();

private:
  std::string _directory_path;
};

#endif

