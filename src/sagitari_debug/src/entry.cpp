#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <message_filters/subscriber.h>
#include <iostream>
using namespace sensor_msgs;
using namespace message_filters;

void subSubCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    std::cout<<1<<std::endl;
    cv::imshow("Tracking", cv_ptr->image);
    cv::waitKey(1);
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "sagitari_debug");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subSub = it.subscribe("Sagitari/debugImage", 1, subSubCallback);
    ros::Rate rate(150);
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }   

    
}