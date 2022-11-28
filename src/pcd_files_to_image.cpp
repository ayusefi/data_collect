/**********************************

    Created on : 12 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "pcd_files_to_image.h"

PcdFilesToImage::PcdFilesToImage(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("directory_path", _directory_path, "");
  ROS_INFO("directory_path: %s", _directory_path.c_str());

  try {
    boost::filesystem::create_directories(_directory_path + "_image");
  }
  catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    std::cout << e.what() << std::endl;
  }
}

void PcdFilesToImage::pcdFilesToImage()
{
  boost::filesystem::path p = _directory_path;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    std::string timestamp_str = (*it).path().stem().string();

    pcl::io::loadPCDFile((*it).path().string(), _pointcloud_msg);
    std::cout << _pointcloud_msg << std::endl;
    pcl::toROSMsg(_pointcloud_msg, _image_msg);
    // cv_bridge::CvImagePtr cv_ptr;

    // cv_ptr = cv_bridge::toCvCopy(_image_msg, sensor_msgs::image_encodings::BGR8);

    // std::stringstream ss;
    // ss << _directory_path  << "_image/" << timestamp_str << ".jpg";
    // cv::imwrite(ss.str(), cv_ptr->image);
    // // ROS_INFO ("Data saved to %s", ss.str ().c_str ());

    *it++;
  }
}