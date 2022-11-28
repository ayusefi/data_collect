#ifndef PCD_FILES_TO_IMAGE_H
#define PCD_FILES_TO_IMAGE_H

/**********************************

    Created on : 12 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <boost/filesystem.hpp>
#include <chrono>

class PcdFilesToImage
{
public:
  PcdFilesToImage(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~PcdFilesToImage(){}

  void pcdFilesToImage();

private:
  std::string _directory_path;

  sensor_msgs::Image _image_msg;
  sensor_msgs::PointCloud2 _pointcloud_msg;
};

#endif

