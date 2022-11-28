#include "data_to_bag.h"

/**********************************

    Created on : 05 October 2022 
    Author     : Abdullah Yusefi

**********************************/

DataToBag::DataToBag(ros::NodeHandle node, ros::NodeHandle private_nh)
{
  private_nh.param<std::string>("dataset_path", _dataset_path, "");
  ROS_INFO("dataset_path: %s", _dataset_path.c_str());

  private_nh.param("directory_names", _directory_names, _directory_names);
  private_nh.param("topic_names", _topic_names, _topic_names);
  private_nh.param("frame_ids", _frame_ids, _frame_ids);
  private_nh.param("data_types", _data_types, _data_types);

  _bag.open(_dataset_path + "output.bag", rosbag::bagmode::Write);
}

void DataToBag::dataToBag()
{


  for(int i=0; i<_topic_names.size(); i++){
    _current_dicrectory = static_cast<std::string>(_directory_names[i]).c_str();
    _current_topic = static_cast<std::string>(_topic_names[i]).c_str();
    _current_frame = static_cast<std::string>(_frame_ids[i]).c_str();
    _current_datatype = static_cast<std::string>(_data_types[i]).c_str();

    _data_types_enum _current_datatype_enum = DataToBag::hashit(_current_datatype);
    switch(_current_datatype_enum){
      case _PointCloud2_enum:
        {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(pointcloudToBag()) std::cout << " \t\tDone in ";
        else std::cout << " Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _Image_enum:
        {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(imageToBag()) std::cout << " \t\tDone in ";
        else std::cout << " Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _Imu_enum:
      {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(imuToBag()) std::cout << " \t\tDone in ";
        else std::cout << "Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _Float64_enum:
      {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(float64ToBag()) std::cout << " \t\tDone in ";
        else std::cout << "Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _NavSatFix_enum:
      {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(navsatfixToBag()) std::cout << " \t\tDone in ";
        else std::cout << "Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _Float32Stamped_enum:
      {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(float32stampedToBag()) std::cout << " \t\tDone in ";
        else std::cout << "Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _Odometry_enum:
      {
        std::cout << "Processing topic: " << _topic_names[i] << std::endl;
        auto start = std::chrono::steady_clock::now();
        if(odometryToBag()) std::cout << " \t\tDone in ";
        else std::cout << "Failed!\n";
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " seconds" << std::endl;
        }
        break;
      case _noSupport_enum:
        std::cout << "data_type: " << _data_types[i] << " is not supported!" << std::endl;
        break;
      default:
        std::cout << "data_type: " << _data_types[i] << " is not supported!" << std::endl;
        break;
    }
  }
}

void DataToBag::timestampStrToRos(const std::string* timestamp_str, ros::Time* time) 
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
  // timestamp_str.erase(remove(timestamp_str.begin(), timestamp_str.end(), '.'), timestamp_str.end());
  std::cout << "odom: " << new_timestamp.str() << std::endl;
  time->fromNSec(std::stoull((new_timestamp).str()));
}

bool DataToBag::pointcloudToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    timestamp_str.insert(10,".");

    sensor_msgs::PointCloud2 pointcloud_msg;
    DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);
    pointcloudFileToRos(&((*it).path().string()), &pointcloud_msg);
    pointcloud_msg.header.frame_id = _current_frame;
    pointcloud_msg.header.stamp = timestamp_ros;
    _bag.write(_current_topic, timestamp_ros, pointcloud_msg);
    *it++;
  }
  return true;
}

bool DataToBag::imageToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);

    sensor_msgs::Image image_msg;
    image_msg.header.frame_id = _current_frame;
    image_msg.header.stamp = timestamp_ros;
    imageFileToRos(&((*it).path().string()), &image_msg);
    _bag.write(_current_topic, timestamp_ros, image_msg);
    *it++;
  }
  return true;
}

bool DataToBag::imuToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    std::string timestamp_str = (*it).path().stem().string();
    
    sensor_msgs::Imu imu_msg;
    imu_msg.header.frame_id = _current_frame;
    imuFileToRos(&((*it).path().string()), &imu_msg);
    
    *it++;
  }
  return true;
}

bool DataToBag::float64ToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);

    std_msgs::Float64 float64_msg;
    float64FileToRos(&((*it).path().string()), &float64_msg);
    _bag.write(_current_topic, timestamp_ros, float64_msg);
    *it++;
  }
  return true;
}

bool DataToBag::navsatfixToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    std::string timestamp_str = (*it).path().stem().string();

    sensor_msgs::NavSatFix fix_msg;
    fix_msg.header.frame_id = _current_frame;
    fixFileToRos(&((*it).path().string()), &fix_msg);
    *it++;
  }
  return true;
}

bool DataToBag::float32stampedToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);

    marti_common_msgs::Float32Stamped float32stamped_msg;
    float32stamped_msg.header.frame_id = _current_frame;
    float32stamped_msg.header.stamp = timestamp_ros;
    float32stampedFileToRos(&((*it).path().string()), &float32stamped_msg);
    _bag.write(_current_topic, timestamp_ros, float32stamped_msg);
    *it++;
  }
  return true;
}

bool DataToBag::odometryToBag()
{
  boost::filesystem::path p = _dataset_path + _current_dicrectory;
  boost::filesystem::directory_iterator it{p};
  while (it != boost::filesystem::directory_iterator{}){
    ros::Time timestamp_ros;
    std::string timestamp_str = (*it).path().stem().string();
    DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);

    nav_msgs::Odometry odometry_msg;
    odometry_msg.header.frame_id = _current_frame;
    odometry_msg.header.stamp = timestamp_ros;
    odometryFileToRos(&((*it).path().string()), &odometry_msg);
    _bag.write(_current_topic, timestamp_ros, odometry_msg);
    *it++;
  }
  return true;
}

void DataToBag::pointcloudFileToRos(const std::string* file_path, sensor_msgs::PointCloud2* pointcloud)
{
  if(pcl::io::loadPCDFile(*file_path, *pointcloud) < 0)
  {
    ROS_ERROR_STREAM("Failed to parse pointcloud from file ('" << file_path << "')");
  }

}

void DataToBag::imageFileToRos(const std::string* file_path, sensor_msgs::Image* image)
{
  cv::Mat image_cv = cv::imread(*file_path, cv::IMREAD_UNCHANGED);
  if (!image_cv.data) std::cout << "Could not open image: " << file_path << std::endl;
  cv_bridge::CvImage image_cv_bridge;
  image_cv_bridge.image = image_cv;
  if (image_cv.type() == CV_8U) {
    image_cv_bridge.encoding = "mono8";
  } else if (image_cv.type() == CV_8UC3) {
    image_cv_bridge.encoding = "bgr8";
  }
  image_cv_bridge.toImageMsg(*image);
}

void DataToBag::imuFileToRos(const std::string* file_path, sensor_msgs::Imu* imu)
{
  std::ifstream inFile(*file_path);
  if (inFile.is_open())
  {
      std::string line;
      while( std::getline(inFile,line) )
      {
          std::stringstream ss(line);
          std::string timestamp_str,
                      linear_x, linear_y, linear_z,
                      angular_x, angular_y, angular_z,
                      orientation_x, orientation_y, orientation_z, orientation_w;
          std::getline(ss,timestamp_str,',');
          std::getline(ss,linear_x,','); 
          std::getline(ss,linear_y,','); 
          std::getline(ss,linear_z,','); 
          std::getline(ss,angular_x,','); 
          std::getline(ss,angular_y,','); 
          std::getline(ss,angular_z,','); 
          std::getline(ss,orientation_x,','); 
          std::getline(ss,orientation_y,','); 
          std::getline(ss,orientation_z,',');
          std::getline(ss,orientation_w,',');

          ros::Time timestamp_ros;
          DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);
          imu->header.stamp = timestamp_ros;
          imu->linear_acceleration.x = std::stod(linear_x);
          imu->linear_acceleration.y = std::stod(linear_y);
          imu->linear_acceleration.z = std::stod(linear_z);
          imu->angular_velocity.x = std::stod(angular_x);
          imu->angular_velocity.y = std::stod(angular_y);
          imu->angular_velocity.z = std::stod(angular_z);
          imu->orientation.x = std::stod(orientation_x);
          imu->orientation.y = std::stod(orientation_y);
          imu->orientation.z = std::stod(orientation_z);
          imu->orientation.w = std::stod(orientation_w);

          _bag.write(_current_topic, timestamp_ros, *imu);
      }
  }
}

void DataToBag::float64FileToRos(const std::string* file_path, std_msgs::Float64* float64)
{
  std::ifstream inFile(*file_path);
  if (inFile.is_open())
  {
      std::string line;
      while( std::getline(inFile,line) )
      {
          std::stringstream ss(line);
          std::string data;
          std::getline(ss,data,',');  
          float64->data = std::stod(data);
      }
  }
}

void DataToBag::fixFileToRos(const std::string* file_path, sensor_msgs::NavSatFix* fix)
{
  std::ifstream inFile(*file_path);
  if (inFile.is_open())
  {
      std::string line;
      while( std::getline(inFile,line) )
      {
          std::stringstream ss(line);
          std::string timestamp_str,latitude, longitude, altitude;
          std::getline(ss,timestamp_str,',');
          std::getline(ss,latitude,','); 
          std::getline(ss,longitude,','); 
          std::getline(ss,altitude,',');
    
          ros::Time timestamp_ros;
          DataToBag::timestampStrToRos(&timestamp_str, &timestamp_ros);
          fix->header.stamp = timestamp_ros;
          fix->latitude = std::stod(latitude);
          fix->longitude = std::stod(longitude);
          fix->altitude = std::stod(altitude);
          _bag.write(_current_topic, timestamp_ros, *fix);
      }
  }
}

void DataToBag::float32stampedFileToRos(const std::string* file_path, marti_common_msgs::Float32Stamped* float32stamped)
{
  std::ifstream inFile(*file_path);
  if (inFile.is_open())
  {
      std::string line;
      while( std::getline(inFile,line) )
      {
          std::stringstream ss(line);
          std::string value;
          std::getline(ss,value,',');  
          float32stamped->value = std::stod(value);
      }
  }
}

void DataToBag::odometryFileToRos(const std::string* file_path, nav_msgs::Odometry* odometry)
{
  std::ifstream inFile(*file_path);
  if (inFile.is_open())
  {
      std::string line;
      while( std::getline(inFile,line) )
      {
          std::stringstream ss(line);
          std::string position_x, position_y, position_z,
                      orientation_x, orientation_y, orientation_z, orientation_w;
          std::getline(ss,position_x,','); 
          std::getline(ss,position_y,','); 
          std::getline(ss,position_z,','); 
          std::getline(ss,orientation_x,','); 
          std::getline(ss,orientation_y,','); 
          std::getline(ss,orientation_z,',');
          std::getline(ss,orientation_w,',');
          odometry->pose.pose.position.x = std::stod(position_x);
          odometry->pose.pose.position.y = std::stod(position_y);
          odometry->pose.pose.position.z = std::stod(position_z);
          odometry->pose.pose.orientation.x = std::stod(orientation_x);
          odometry->pose.pose.orientation.y = std::stod(orientation_y);
          odometry->pose.pose.orientation.z = std::stod(orientation_z);
          odometry->pose.pose.orientation.w = std::stod(orientation_w);
      }
  }
}

DataToBag::_data_types_enum DataToBag::hashit(std::string const& in_string){
  if(in_string=="PointCloud2") return _PointCloud2_enum;
  if(in_string=="Image")  return _Image_enum;
  if(in_string=="Imu")  return _Imu_enum;
  if(in_string=="Float64") return _Float64_enum;
  if(in_string=="NavSatFix") return _NavSatFix_enum;
  if(in_string=="Float32Stamped") return _Float32Stamped_enum;
  if(in_string=="Odometry") return _Odometry_enum;
  else  return _noSupport_enum;
}
