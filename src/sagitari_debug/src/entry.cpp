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

cv::VideoWriter video = cv::VideoWriter("/tmp/test2.mpg", CV_FOURCC('D', 'I', 'V', 'X'), 30, cv::Size(1280, 720));
int min_h = 0, max_h = 180, min_v = 0, max_v = 255, min_s = 0, max_s = 255;
void subSubCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv::Mat showMat;
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    cv::circle(cv_ptr->image, cv::Point(cv_ptr->image.cols, cv_ptr->image.rows) / 2, 25, cv::Scalar(255, 255, 255), 1);
    // cv::cvtColor(cv_ptr->image,showMat,CV_BGR2HSV);
    // cv::inRange(showMat, cv::Scalar(min_h, min_v, min_s), cv::Scalar(max_h, max_v, max_s), showMat);
    cv_ptr->image.copyTo(showMat);
    cv::imshow("Tracking", showMat);
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
    }
}
void subSubCallback2(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    video << (cv_ptr->image);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "sagitari_debug");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subSub = it.subscribe("Sagitari/debugImage", 1, subSubCallback);
    image_transport::Subscriber subSub2 = it.subscribe("Sagitari/debugImage2", 1, subSubCallback2);
    debugPublisher = nh.advertise<uart_process_2::uart_receive>("uart_receive", 1);
    cv::namedWindow("Tracking");
    cv::createTrackbar("H-min", "Tracking", &min_h, 255);
    cv::createTrackbar("H-max", "Tracking", &max_h, 255);
    cv::createTrackbar("S-min", "Tracking", &min_s, 255);
    cv::createTrackbar("S-max", "Tracking", &max_s, 255);
    cv::createTrackbar("V-min", "Tracking", &min_v, 255);
    cv::createTrackbar("V-max", "Tracking", &max_v, 255);
    ros::Rate rate(150);
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }
}