/**********************************

    Created on : 01 December 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "ti_radar_saver.h"

TiRadarSaver::TiRadarSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("ti_radar_topic", _ti_radar_topic, "");
  ROS_INFO("ti_radar_topic: %s", _ti_radar_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }

  MyFile.open(_output_path + "ti_radar.txt");

  ti_radar_sub = node.subscribe(_ti_radar_topic, 10, &TiRadarSaver::tiRadarCallback, this);
}

void TiRadarSaver::tiRadarCallback(const ti_mmwave_rospkg::RadarScan::ConstPtr& ti_radar_msg)
{
  std::stringstream ss;
  ss << ti_radar_msg->header.stamp.sec << "." << ti_radar_msg->header.stamp.nsec;

  // std::cout << ti_radar_msg->point_id << '\n';

  MyFile << std::setprecision(10) << ss.str() <<','<<ti_radar_msg->point_id<<','<<ti_radar_msg->x<<','<<ti_radar_msg->y<<','<<ti_radar_msg->z<<','<<
            ti_radar_msg->range<<','<<ti_radar_msg->velocity<<','<<ti_radar_msg->doppler_bin<<','<<ti_radar_msg->bearing<<','<<
            ti_radar_msg->intensity<<'\n';
}
