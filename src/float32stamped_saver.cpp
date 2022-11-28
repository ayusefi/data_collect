/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "float32stamped_saver.h"

Float32stampedSaver::Float32stampedSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("float32stamped_topic", _float32stamped_topic, "");
  ROS_INFO("float32stamped_topic: %s", _float32stamped_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  float32stamped_sub = node.subscribe(_float32stamped_topic, 1, &Float32stampedSaver::float32stampedCallback, this);
}

void Float32stampedSaver::float32stampedCallback(const marti_common_msgs::Float32Stamped::ConstPtr& float32stamped_msg)
{
  std::stringstream ss;
  ss << float32stamped_msg->header.stamp.sec << "." << float32stamped_msg->header.stamp.nsec;
  std::ofstream MyFile(_output_path + ss.str() +".txt");
  MyFile << std::setprecision(10) << float32stamped_msg->value;
  MyFile.close();
  // ROS_INFO("Float32stamped value: [%f]", float32stamped_msg->value);
}
