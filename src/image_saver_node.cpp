/**********************************

    Created on : 04 October 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "image_saver.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_saver_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    ImageSaver image_saver(node, private_nh);

    // ros::Rate loop_rate(30);
    while(ros::ok())
    {
        ros::spinOnce();
        // loop_rate.sleep();
    }

    return 0;
}