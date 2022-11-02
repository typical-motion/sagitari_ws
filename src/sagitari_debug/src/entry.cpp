#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <message_filters/subscriber.h>
#include <uart_process_2/uart_receive.h>
#include <sagitari_debug/sagitari_img_debug.h>
#include <iostream>
using namespace sensor_msgs;
using namespace message_filters;
using namespace std;

ros::Publisher debugPublisher;

bool screenshot = false;
void debugImageCallback(const sagitari_debug::sagitari_img_debug &msg)
{
    try
    {
        cv::Mat showMat;
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(msg.image, "bgr8");
        cv::circle(cv_ptr->image, cv::Point(cv_ptr->image.cols, cv_ptr->image.rows) / 2, 25, cv::Scalar(255, 255, 255), 1);
        // cv::cvtColor(cv_ptr->image,showMat,CV_BGR2HSV);
        // cv::inRange(showMat, cv::Scalar(min_h, min_v, min_s), cv::Scalar(max_h, max_v, max_s), showMat);
        cv_ptr->image.copyTo(showMat);
        // if(msg.title != "Tracking") return;
        // video << (cv_ptr->image);
        cv::imshow(msg.title, showMat);
    }
    catch (cv_bridge::Exception e)
    {
        std::cout << "SagitariNode Debug throws an exception what(): " << e.what() << " while processing " << msg.title << std::endl;
    }
}
void originalImageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    // video << (cv_ptr->image);
    if (screenshot)
    {
        screenshot = false;
        cv::imwrite("/tmp/screenshot_" + std::to_string(msg.get()->header.seq) + "_.jpg", cv_ptr->image);
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "sagitari_debug");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    ros::Subscriber debugImageSubscriber = nh.subscribe("Sagitari/debugImage", 1, debugImageCallback);
    ros::Subscriber trackingFailedSubscriber = nh.subscribe("Sagitari/trackingFailedImage", 1, debugImageCallback);
    image_transport::Subscriber originalImageSubscriber = it.subscribe("Sagitari/originalImage", 1, originalImageCallback);
    debugPublisher = nh.advertise<uart_process_2::uart_receive>("uart_receive", 1);
    /*
    cv::namedWindow("Tracking");
    cv::createTrackbar("H-min", "Tracking", &min_h, 255);
    cv::createTrackbar("H-max", "Tracking", &max_h, 255);
    cv::createTrackbar("S-min", "Tracking", &min_s, 255);
    cv::createTrackbar("S-max", "Tracking", &max_s, 255);
    cv::createTrackbar("V-min", "Tracking", &min_v, 255);
    cv::createTrackbar("V-max", "Tracking", &max_v, 255);
    */
    ros::Rate rate(30);
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
        int key = cv::waitKey(1);
        if (key == 'r')
        {
            uart_process_2::uart_receive _data;
            _data.pitch = -9080;
            debugPublisher.publish(_data);
        }
        else if (key == 'q')
        {
            exit(0);
        }
        else if (key == 's')
        {
            screenshot = true;
        } else if(key == 'p') {
            cv::waitKey(0);
        }
    }
}