#ifndef DATA_TO_BAG_H
#define DATA_TO_BAG_H

/**********************************

    Created on : 05 Ocotober 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <pcl_ros/point_cloud.h>
#include <rosbag/bag.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <marti_common_msgs/Float32Stamped.h>
#include <chrono>
#include <vector>

class DataToBag
{
public:
  DataToBag(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~DataToBag(){}

  void dataToBag();

  enum _data_types_enum{
    _PointCloud2_enum,
    _Image_enum,
    _Imu_enum,
    _Float64_enum,
    _NavSatFix_enum,
    _Float32Stamped_enum,
    _Odometry_enum,
    _noSupport_enum
  };

private:
  void timestampStrToRos(const std::string* timestamp_str, ros::Time* time);

  bool pointcloudToBag();
  bool imageToBag();
  bool imuToBag();
  bool float64ToBag();
  bool navsatfixToBag();
  bool float32stampedToBag();
  bool odometryToBag();

  void pointcloudFileToRos(const std::string* file_path, sensor_msgs::PointCloud2* pointcloud);
  void imageFileToRos(const std::string* file_path, sensor_msgs::Image* image);
  void imuFileToRos(const std::string* file_path, sensor_msgs::Imu* imu);
  void float64FileToRos(const std::string* file_path, std_msgs::Float64* float64);
  void fixFileToRos(const std::string* file_path, sensor_msgs::NavSatFix* fix);
  void float32stampedFileToRos(const std::string* file_path, marti_common_msgs::Float32Stamped* float32stamped);
  void odometryFileToRos(const std::string* file_path, nav_msgs::Odometry* odometry);

  _data_types_enum hashit(std::string const& in_string);
  std::string _dataset_path;
  XmlRpc::XmlRpcValue _directory_names, _topic_names, _frame_ids, _data_types;
  std::string _current_dicrectory, _current_topic, _current_frame, _current_datatype;
  rosbag::Bag _bag;
};

#endif

