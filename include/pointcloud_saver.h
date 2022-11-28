#ifndef POINTCLOUD_SAVER_H
#define POINTCLOUD_SAVER_H

#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <boost/filesystem.hpp>

class PointcloudSaver
{
public:
  PointcloudSaver(ros::NodeHandle node, ros::NodeHandle private_nh);
  ~PointcloudSaver(){}

private:
  void pointcloudCallback(const boost::shared_ptr<const pcl::PCLPointCloud2>& cloud);
  ros::Subscriber pointcloud_sub;
  std::string _pointcloud_topic, _output_path;
};

#endif
