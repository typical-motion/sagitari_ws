#include "camera_pkg_daheng/Daheng_camera.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "DahengCameraPicture_publish");
	
    ros::NodeHandle nh;
   
	image_transport::ImageTransport it(nh);
    //image_transport::Publisher pub_high = it.advertise("DahuaCamera/HighDims",5);
    image_transport::Publisher pub_low = it.advertise("DahuaCamera/LowDims",1);
    ros::Rate rate(150);
    GX_STATUS status = GX_STATUS_SUCCESS;
    
    cout << "Init Lib.........." << endl;
    status = GXInitLib();//初始化GXlib
    if (status != GX_STATUS_SUCCESS)
    {
        cout << "Init Lib fail !" << endl;
        return 0;
    }
    else
    {
        cout << "Init Lib success !" << endl;
    }
    GX_DEV_HANDLE hDevice = NULL;
    status = GX_STATUS_SUCCESS;
    uint32_t nDeviceNum = 0;
    status = GXUpdateDeviceList(&nDeviceNum, 1000);//更新GX相机设备表，设备个数
    uint64_t time_stamp = 0;
    

    if (status == GX_STATUS_SUCCESS && nDeviceNum> 0)
    {
        cout << "Found camera number: " << nDeviceNum << endl;
        status = OpenGxDevice(1, &hDevice);
        if(status == GX_STATUS_SUCCESS && hDevice != NULL)
        {
            cout << "Open camera " << nDeviceNum << " success!" << endl;
        }
        PGX_FRAME_BUFFER pFrameBuffer;
        status = SetBalanceRatio(hDevice, 1.3828, 1, 1.6992);//设置白平衡 
        status = SetExposureTime(hDevice, 5000);//设置曝光
        double ExposureTime = GetExposureTime(hDevice);
        status = SetROI(hDevice, 1280,720);//设置ROI
        cout << "ExposureTime = " << ExposureTime << endl;
        cout << "GXStreamOn....." << endl;
        status = GXStreamOn(hDevice);


        if(status == GX_STATUS_SUCCESS)
        {
            cout << "GXStreamOn success !" << endl; 
            cv::Mat frame_mat;
            while (ros::ok())
            {
                status = GXDQBuf(hDevice, &pFrameBuffer, 1000);
                if (pFrameBuffer->nStatus == GX_FRAME_STATUS_SUCCESS)
                {
                    char* pRGB24Buf = new char[pFrameBuffer->nWidth * pFrameBuffer->nHeight * 3];
                    if (pRGB24Buf != NULL)
                    {
                        DX_BAYER_CONVERT_TYPE cvtype = RAW2RGB_NEIGHBOUR3;
                        DX_PIXEL_COLOR_FILTER nBayerType = DX_PIXEL_COLOR_FILTER(BAYERBG);
                        bool bFlip = false;
                        VxInt32 DxStatus = DxRaw8toRGB24 (pFrameBuffer->pImgBuf, pRGB24Buf, pFrameBuffer->nWidth, pFrameBuffer->nHeight, cvtype, nBayerType, bFlip);
                        if(DxStatus == DX_OK)
                        {
                            frame_mat = cv::Mat(pFrameBuffer->nHeight, pFrameBuffer->nWidth, CV_8UC3, pRGB24Buf);
                        }
                        if(!frame_mat.empty())
                        {
                            #ifdef DEBUG_
                            imshow("GX_img",frame_mat);
                            if(waitKey(1) == 'q') break;
                            #endif
                            std_msgs::Header head_img;
                            head_img.stamp = ros::Time(pFrameBuffer->nTimestamp * pow(10,-9),pFrameBuffer->nTimestamp - 1e9 *(int)(pFrameBuffer->nTimestamp * 1e-9));
                            //std::cout << pFrameBuffer->nTimestamp << std::endl;
                            sensor_msgs::ImagePtr msg_low = cv_bridge::CvImage(head_img,"bgr8",frame_mat).toImageMsg();
                            //cout << "debug" << endl;
                            pub_low.publish(msg_low);
                        }
                        delete []pRGB24Buf;
                        pRGB24Buf = NULL;
                        status = GXQBuf(hDevice, pFrameBuffer);
                        rate.sleep();
                    }
                }
            }
        }
            status = GXStreamOff(hDevice);
            status = GXCloseDevice(hDevice);
            if(status == GX_STATUS_SUCCESS && hDevice == NULL)
            {
                cout << "Close camera " << nDeviceNum << "success!" << endl;
            }
    }
    else
    {
        cout << "GXcamera not found." << endl;
    }

    status = GXCloseLib();
    if (status != GX_STATUS_SUCCESS)
    {
        cout << "Close Lib fail !" << endl;
        return 0;
    }
    else
    {
        cout << "Close Lib success !" << endl;
    }

    return 0;
}
