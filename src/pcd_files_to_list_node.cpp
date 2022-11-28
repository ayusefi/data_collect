/**********************************

    Created on : 06 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "pcd_files_to_list.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pcd_files_to_list_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    PcdFilesToList pcd_files_to_list(node, private_nh);
    
    auto start = std::chrono::steady_clock::now();
    pcd_files_to_list.pcdFilesToList();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "\nTotal Process Time: " << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " s" << std::endl;
    return 0;
}