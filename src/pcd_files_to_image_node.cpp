/**********************************

    Created on : 12 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "pcd_files_to_image.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pcd_files_to_image_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    PcdFilesToImage pcd_files_to_image(node, private_nh);
    
    auto start = std::chrono::steady_clock::now();
    pcd_files_to_image.pcdFilesToImage();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "\nTotal Process Time: " << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " s" << std::endl;
    return 0;
}