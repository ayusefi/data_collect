/**********************************

    Created on : 06 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "pcd_files_to_list.h"

PcdFilesToList::PcdFilesToList(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("directory_path", _directory_path, "");
  ROS_INFO("directory_path: %s", _directory_path.c_str());
}

void PcdFilesToList::pcdFilesToList()
{
  std::ofstream MyFile(_directory_path + ".csv");
  MyFile << "timestamp,file_name\n";

  boost::filesystem::path p = _directory_path;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    std::string timestamp_str = (*it).path().stem().string();
    timestamp_str.erase(remove(timestamp_str.begin(), timestamp_str.end(), '.'), timestamp_str.end());
        std::string line;
        MyFile << std::setprecision(10) << timestamp_str << ',' << (*it).path().stem().string() << ".pcd" << '\n';
    *it++;
  }
  MyFile.close();

}