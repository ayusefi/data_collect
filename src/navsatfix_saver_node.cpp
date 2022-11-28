/**********************************

    Created on : 28 November 2022 
    Author     : Abdullah Yusefi

**********************************/

#include <ros/ros.h>
#include "navsatfix_saver.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "navsatfix_saver_node");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    NavsatfixSaver navsatfix_saver(node, private_nh);

    // ros::Rate loop_rate(30);
    while(ros::ok())
    {
        ros::spinOnce();
        // loop_rate.sleep();
    }

    return 0;
}