#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

/**********************************

    Created on : 04 Ocotober 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <boost/filesystem.hpp>

class ImageSaver
{
public:
  ImageSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~ImageSaver(){}

private:
  void imageCallback(const sensor_msgs::ImageConstPtr& image_msg);
  ros::Subscriber image_sub;
  std::string _image_topic, _output_path;
};

#endif

