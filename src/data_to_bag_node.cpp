/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "data_to_bag.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "data_to_bag_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    DataToBag data_to_bag(node, private_nh);
    
    auto start = std::chrono::steady_clock::now();
    data_to_bag.dataToBag();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "\nTotal Process Time: " << std::chrono::duration <double, std::milli> (diff).count()/1000.0<< " s" << std::endl;
    return 0;
}