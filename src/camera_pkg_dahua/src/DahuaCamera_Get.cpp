#include "DahuaCamera_Get.h"

extern IStreamSourcePtr &get_connect_with_camare(ICameraPtr &cameraSptr);
extern bool disconnect_fram(ICameraPtr &cameraSptr, IStreamSourcePtr &StreamSourcePtr);
extern int32_t getResolution(ICameraPtr &cameraSptr, int64_t &nWidth, int64_t &nHeight);
extern int32_t setResolution(ICameraPtr &cameraSptr, int nWidth, int nHeight);
extern int32_t setROI(ICameraPtr &cameraSptr, int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight);
extern int32_t setGainRaw(ICameraPtr &cameraSptr, double dGainRaw);
extern int32_t setBalanceRatio(ICameraPtr &cameraSptr, double dRedBalanceRatio, double dGreenBalanceRatio, double dBlueBalanceRatio);
extern int32_t setGamma(ICameraPtr &cameraSptr, double dGamma);
extern int32_t setExposureTime(ICameraPtr &cameraSptr, double dExposureTime, bool bAutoExposure = false);
extern int32_t setBalanceRatio_Auto(ICameraPtr &cameraSptr);
ICameraPtr cameraSptr;
IStreamSourcePtr streamPtr;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "DahuaCameraPicture_publish");

	ros::NodeHandle nh;

	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub_low = it.advertise("DahuaCamera/LowDims", 1);
	streamPtr = get_connect_with_camare(cameraSptr);
	setGainRaw(cameraSptr, 1);
	setBalanceRatio(cameraSptr, 1.15, 1.0, 1.57); //1.37, 1.0, 1.49//115 100 157  //设置白平衡
	//setBalanceRatio_Auto(cameraSptr);
	setGamma(cameraSptr, 1);		   //设置相机伽马值
	setExposureTime(cameraSptr, 5000); //设置相机曝光

	cout << "debug" << endl;
	CFrame tFrame;
	streamPtr->getFrame(tFrame, 150);
	int nBGRBufferSize = tFrame.getImageWidth() * tFrame.getImageHeight() * 3;
	uint8_t *pBGRbuffer = new uint8_t[nBGRBufferSize];
	IMGCNV_SOpenParam openParam;
	openParam.width = tFrame.getImageWidth();
	openParam.height = tFrame.getImageHeight();
	openParam.paddingX = tFrame.getImagePadddingX();
	openParam.paddingY = tFrame.getImagePadddingY();
	openParam.dataSize = tFrame.getImageSize();
	openParam.pixelForamt = tFrame.getImagePixelFormat();

	Rect low_dims_rect(0, 0, 1024, 480);
	ros::Rate rate(200);

	while (nh.ok())
	{
		CFrame frame;
		streamPtr->getFrame(frame, 150);
		IMGCNV_EErr status = IMGCNV_ConvertToBGR24((unsigned char *)frame.getImage(), &openParam, pBGRbuffer, &nBGRBufferSize);
		if (IMGCNV_SUCCESS != status)
		{
			delete[] pBGRbuffer;
		}

		Mat src_image = Mat(480, 1024, CV_8UC3, pBGRbuffer);
		sensor_msgs::ImagePtr msg_low = cv_bridge::CvImage(std_msgs::Header(), "bgr8", src_image).toImageMsg();
		if (src_image.data)
			pub_low.publish(msg_low);
		else
			break;
		rate.sleep();
	}
	delete[] pBGRbuffer;
	disconnect_fram(cameraSptr, streamPtr);
}
