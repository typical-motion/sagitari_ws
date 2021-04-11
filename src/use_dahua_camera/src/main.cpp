#include "../include/use_dahua_camera/get_fram.h"
#include <ros/ros.h>
#include<cv_bridge/cv_bridge.h>
#include <stdio.h>
#include<image_transport/image_transport.h>
#include<string.h>

IStreamSourcePtr &get_connect_with_camare(ICameraPtr &cameraSptr);
bool disconnect_fram(ICameraPtr &cameraSptr,IStreamSourcePtr & StreamSourcePtr);
int32_t getResolution(ICameraPtr& cameraSptr, int64_t &nWidth, int64_t &nHeight);
int32_t setResolution(ICameraPtr& cameraSptr, int nWidth, int nHeight);
int32_t setROI(ICameraPtr& cameraSptr, int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight);

ICameraPtr cameraSptr;
IStreamSourcePtr streamPtr; 
static void process_program_exit_Int(int)//due to disconnect with camera
{
	char * argv_program = NULL;
	disconnect_fram(cameraSptr, streamPtr);
}


static void process_program_exit_abort(int)//due to disconnect with camera
{
	char * argv_program = NULL;
	disconnect_fram(cameraSptr, streamPtr);
}


int main(int argc , char** argv)
{
    Mat src_image;
    streamPtr = get_connect_with_camare(cameraSptr);
	signal(SIGABRT,process_program_exit_abort);
	signal(SIGINT,process_program_exit_Int);
    while(true)
    {
        CFrame frame;	
	    streamPtr->getFrame(frame,150);
	    /*RGB8 Convert BGR24*/
	    int nBGRBufferSize = frame.getImageWidth() * frame.getImageHeight() * 3; 
	    uint8_t *pBGRbuffer = new uint8_t[nBGRBufferSize];
	    uint8_t *pSrcData = new uint8_t[nBGRBufferSize];
	    memcpy(pSrcData,frame.getImage(),frame.getImageSize());
	    IMGCNV_SOpenParam openParam; 
	    openParam.width     = frame.getImageWidth(); 
	    openParam.height    = frame.getImageHeight(); 
	    openParam.paddingX  = frame.getImagePadddingX(); 
	    openParam.paddingY  = frame.getImagePadddingY(); 
	    openParam.dataSize   = frame.getImageSize(); 
	    openParam.pixelForamt = frame.getImagePixelFormat(); 
	    IMGCNV_EErr status = IMGCNV_ConvertToBGR24(pSrcData, &openParam, pBGRbuffer, &nBGRBufferSize);  
	    if (IMGCNV_SUCCESS != status) 
	    { 
		    delete[] pBGRbuffer;     
	    } 
	    //src_image = Mat(frame.getImageHeight(),frame.getImageWidth(),CV_8UC3,pBGRbuffer);
	    src_image = Mat(480,640,CV_8UC3,pBGRbuffer);
		imshow("src",src_image);
		waitKey(1);
        delete[] pBGRbuffer;
		delete[] pSrcData;
    }
    disconnect_fram(cameraSptr, streamPtr);
    return 0;
}