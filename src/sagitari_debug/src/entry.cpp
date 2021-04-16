#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <uart_process_2/uart_receive.h>
#include <image_transport/image_transport.h>
#include <message_filters/subscriber.h>
#include <iostream>
using namespace sensor_msgs;
using namespace message_filters;
ros::Publisher debugPublisher;

cv::VideoWriter video = cv::VideoWriter("/tmp/test2.avi", CV_FOURCC('f', 'l', 'v', '1'), 30, cv::Size(1280, 1024));
bool screenshot = false;
void subSubCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    cv::circle(cv_ptr->image, cv::Point(cv_ptr->image.cols, cv_ptr->image.rows) / 2, 25, cv::Scalar(255, 255, 255), 1);
    cv::imshow("Tracking", cv_ptr->image);
    int key = cv::waitKey(1);
    if (key == 'r')
    {
        uart_process_2::uart_receive _data;
        _data.pitch = -9080;
        debugPublisher.publish(_data);
    }
    else if (key == 'q')
    {
        video.release();
        exit(0);
    } else if(key == 's')
    {
        screenshot = true;
    }
}
void subSubCallback2(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    video << (cv_ptr->image);
    if(screenshot) {
        screenshot = false;
        cv::imwrite("/tmp/screenshot_" + std::to_string(msg.get()->header.seq) + "_.jpg", cv_ptr->image);
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "sagitari_debug");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subSub = it.subscribe("Sagitari/debugImage", 1, subSubCallback);
    image_transport::Subscriber subSub2 = it.subscribe("Sagitari/debugImage2", 1, subSubCallback2);
    debugPublisher = nh.advertise<uart_process_2::uart_receive>("uart_receive", 1);
    ros::Rate rate(150);
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }
}