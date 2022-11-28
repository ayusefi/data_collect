/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "navsatfix_saver.h"

NavsatfixSaver::NavsatfixSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("navsatfix_topic", _navsatfix_topic, "");
  ROS_INFO("navsatfix_topic: %s", _navsatfix_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  navsatfix_sub = node.subscribe(_navsatfix_topic, 1, &NavsatfixSaver::navsatfixCallback, this);
}

void NavsatfixSaver::navsatfixCallback(const sensor_msgs::NavSatFix::ConstPtr& navsatfix_msg)
{
  std::stringstream ss;
  ss << navsatfix_msg->header.stamp.sec << "." << navsatfix_msg->header.stamp.nsec;
  std::ofstream MyFile(_output_path + ss.str() +".txt");
  MyFile << std::setprecision(10) << navsatfix_msg->latitude << ',' << navsatfix_msg->longitude << ',' << navsatfix_msg->altitude;
  MyFile.close();
  // ROS_INFO("NavSatFix latitude: [%f], longitude: [%f], altitude: [%f]", navsatfix_msg->latitude, navsatfix_msg->longitude, navsatfix_msg->altitude);
}
