/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "float64_saver.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "float64_saver_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    Float64Saver float64_saver(node, private_nh);

    // ros::Rate loop_rate(30);
    while(ros::ok())
    {
        ros::spinOnce();
        // loop_rate.sleep();
    }

    return 0;
}