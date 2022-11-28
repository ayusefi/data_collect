#include "image_saver.h"

/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

ImageSaver::ImageSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("image_topic", _image_topic, "");
  ROS_INFO("image_topic: %s", _image_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  image_sub = node.subscribe(_image_topic, 1, &ImageSaver::imageCallback, this);
}

void ImageSaver::imageCallback(const sensor_msgs::ImageConstPtr& image_msg)
{
  cv::Mat image;
  try
  {
    image = cv_bridge::toCvShare(image_msg, std::string("bgr8"))->image;
    if(!image.empty()){
      std::stringstream ss;
      ss << _output_path << image_msg->header.stamp << ".jpg";
      cv::imwrite(ss.str(), image);
      // ROS_INFO ("Data saved to %s", ss.str ().c_str ());
    }
    else{
      ROS_WARN("Couldn't save image, no data!");
    }
  } catch(cv_bridge::Exception)
  {
    ROS_ERROR("Unable to convert %s image to %s", image_msg->encoding.c_str(), std::string("bgr8").c_str());
  }

}
