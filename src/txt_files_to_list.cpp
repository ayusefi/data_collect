/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include "txt_files_to_list.h"

TxtFileToList::TxtFileToList(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("directory_path", _directory_path, "");
  ROS_INFO("directory_path: %s", _directory_path.c_str());

  private_nh.param("variable_names", _variable_names, _variable_names);

}

void TxtFileToList::txtFileToList()
{
  std::ofstream MyFile(_directory_path + ".csv");
  MyFile << "timestamp" <<',';
  for(int i=0; i<_variable_names.size()-1;i++)
  {
    MyFile << _variable_names[i] <<',';
  }
  MyFile << _variable_names[_variable_names.size()-1] <<'\n';

  std::string variable_values[_variable_names.size()];

  boost::filesystem::path p = _directory_path;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    // ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    timestamp_str.erase(remove(timestamp_str.begin(), timestamp_str.end(), '.'), timestamp_str.end());

    // timestampStrToRos(&timestamp_str, &timestamp_ros);
    std::ifstream inFile((*it).path().string());
    if (inFile.is_open())
    {
        std::string line;
        while( std::getline(inFile,line) )
        { MyFile << std::setprecision(10) << timestamp_str << ',';
          std::stringstream ss(line);
          for(int i=0;i<_variable_names.size()-1;i++)
          {
            std::getline(ss,variable_values[i],','); 
            MyFile << std::setprecision(10) << variable_values[i] << ',';
          }
          std::getline(ss,variable_values[_variable_names.size()-1],',');
          MyFile << std::setprecision(10) << variable_values[_variable_names.size()-1] << '\n';
        }
    }
    *it++;
  }
  MyFile.close();

}

void TxtFileToList::timestampStrToRos(const std::string* timestamp_str, ros::Time* time) 
{
  std::stringstream ss(*timestamp_str);
  std::stringstream new_timestamp;
  std::string word;
  while (!ss.eof()) {
      getline(ss, word, '.');
      while(word.size() < 9)
      {
        word = word + "0";
      }
      new_timestamp << word;

  }
  std::string timestamp_final = new_timestamp.str();
  timestamp_final.erase(remove(timestamp_final.begin(), timestamp_final.end(), '.'), timestamp_final.end());
  time->fromNSec(std::stoull(timestamp_final));
}
