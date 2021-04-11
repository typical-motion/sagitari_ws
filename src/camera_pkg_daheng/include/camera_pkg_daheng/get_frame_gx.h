#ifndef GET_FRAME_GX_H
#define GET_FRAME_GX_H

#include <iostream>

using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;
#include "DxImageProc.h"
#include "GxIAPI.h"

#include <arpa/inet.h> //used by linux
#include <signal.h>


GX_STATUS OpenGxDevice(int DeviceID, GX_DEV_HANDLE* hDevice);//打开ID为 DeviceID的相机

bool get_mat_from_RAW(PGX_FRAME_BUFFER &pFrameBuffer, cv::Mat &frame_mat);//从数据源抓取图像，速度较慢，建议不使用该函数，建议直接在main中处理

GX_STATUS SetBalanceRatio(GX_DEV_HANDLE hDevice, double red_rate, double green_rate, double blue_rate);

GX_STATUS SetExposureTime(GX_DEV_HANDLE hDevice, double exposure_time);

GX_STATUS SetROI(GX_DEV_HANDLE hDevice,int Width, int Height);//设置ROI，注意宽度不超过1280，长度不超过1024

double GetExposureTime(GX_DEV_HANDLE hDevice);


#endif 