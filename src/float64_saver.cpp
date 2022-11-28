/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "float64_saver.h"

Float64Saver::Float64Saver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("float64_topic", _float64_topic, "");
  ROS_INFO("float64_topic: %s", _float64_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  float64_sub = node.subscribe(_float64_topic, 1, &Float64Saver::float64Callback, this);
}

void Float64Saver::float64Callback(const std_msgs::Float64::ConstPtr& float64_msg)
{
  ros::Time stamp = ros::Time::now();
  std::stringstream ss;
  ss << stamp.sec << "." << stamp.nsec;
  std::ofstream MyFile(_output_path + ss.str() +".txt");
  MyFile << std::setprecision(10) << float64_msg->data;
  MyFile.close();
  // ROS_INFO("Float64 data: [%f]", float64_msg->data);
}
