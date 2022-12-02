#include "pointcloud_saver.h"

/**********************************

    Created on : 03 October 2022 
    Author     : Abdullah Yusefi

**********************************/

PointcloudSaver::PointcloudSaver(ros::NodeHandle node, ros::NodeHandle private_nh)
{

  private_nh.param<std::string>("pointcloud_topic", _pointcloud_topic, "");
  ROS_INFO("pointcloud_topic: %s", _pointcloud_topic.c_str());

  private_nh.param<std::string>("output_path", _output_path, "");
  ROS_INFO("output_path: %s", _output_path.c_str());
  try {
    boost::filesystem::create_directories(_output_path);
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }
  pointcloud_sub = node.subscribe(_pointcloud_topic, 10, &PointcloudSaver::pointcloudCallback, this);
}

void PointcloudSaver::pointcloudCallback(const boost::shared_ptr<const pcl::PCLPointCloud2>& cloud)
{

  if ((cloud->width * cloud->height) == 0)
    return;

  // ROS_INFO ("Received %d data points in frame %s with the following fields: %s",
  //   (int)cloud->width * cloud->height,
  //   cloud->header.frame_id.c_str (),
  //   pcl::getFieldsList (*cloud).c_str ());

  Eigen::Vector4f v = Eigen::Vector4f::Zero ();
  Eigen::Quaternionf q = Eigen::Quaternionf::Identity ();

  std::stringstream ss;

  ss << _output_path << cloud->header.stamp << ".pcd";
  
  // ROS_INFO ("Data saved to %s", ss.str ().c_str ());

  pcl::PCDWriter writer;

  writer.writeBinaryCompressed (ss.str (), *cloud, v, q);

}
