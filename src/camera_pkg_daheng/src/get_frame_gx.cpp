#include "camera_pkg_daheng/get_frame_gx.h"

GX_STATUS OpenGxDevice(int DeviceID, GX_DEV_HANDLE* hDevice_p)
{
    GX_STATUS status = GX_STATUS_SUCCESS;
    GX_OPEN_PARAM stOpenParam;
    stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
    stOpenParam.openMode = GX_OPEN_INDEX;
    stOpenParam.pszContent = "1";
    status = GXOpenDevice(&stOpenParam, hDevice_p);
    return status;
}


bool get_mat_from_RAW(PGX_FRAME_BUFFER &pFrameBuffer, cv::Mat &frame_mat)
{
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
            cv::Mat(1024, 1280, CV_8UC3, pRGB24Buf).copyTo(frame_mat);
            }
            else
            {
                if(pRGB24Buf != NULL)
                {
                    delete []pRGB24Buf;
                    pRGB24Buf = NULL;
                }
                return false;
            }
            delete []pRGB24Buf;
            pRGB24Buf = NULL;
            return true;
            //cout << frame_mat << endl;
        }
        else
        {
            return false;
        }
        
    }
}

GX_STATUS SetBalanceRatio(GX_DEV_HANDLE hDevice, double red_rate, double green_rate, double blue_rate)//设置白平衡
{
    GX_STATUS status;
    status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_RED);
    GX_FLOAT_RANGE ratioRange;
    status = GXGetFloatRange(hDevice, GX_FLOAT_BALANCE_RATIO, &ratioRange);
    ratioRange.dMin = red_rate;
    ratioRange.dMax = red_rate;
    //设 置 最 小 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMin);
    //设 置 最 大 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMax);
    //红色
    status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_GREEN);
    ratioRange.dMin = green_rate;
    ratioRange.dMax = green_rate;
    //设 置 最 小 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMin);
    //设 置 最 大 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMax);
    //绿色
    status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_BLUE);
    ratioRange.dMin = blue_rate;
    ratioRange.dMax = blue_rate;
    //设 置 最 小 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMin);
    //设 置 最 大 白 平 衡 系 数
    status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, ratioRange.dMax);
    //蓝色

    //status = GXSetEnum(hDevice, GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_ONCE);
}

GX_STATUS SetExposureTime(GX_DEV_HANDLE hDevice, double exposure_time)//设置曝光
{
    GX_STATUS status;
    GX_FLOAT_RANGE shutterRange;
    status = GXGetFloatRange(hDevice, GX_FLOAT_EXPOSURE_TIME, &shutterRange);
    shutterRange.dMin = exposure_time;
    shutterRange.dMax = exposure_time;
    //设 置 最 小 曝 光 值
    status = GXSetFloat(hDevice, GX_FLOAT_EXPOSURE_TIME, shutterRange.dMin);
    //设 置 最 大 曝 光 值
    status = GXSetFloat(hDevice, GX_FLOAT_EXPOSURE_TIME, shutterRange.dMax);
}
double GetExposureTime(GX_DEV_HANDLE hDevice)
{
    GX_STATUS status;
    double exposure_time;
    status = GXGetFloat(hDevice, GX_FLOAT_EXPOSURE_TIME, &exposure_time);
    return exposure_time;
}

GX_STATUS SetROI(GX_DEV_HANDLE hDevice,int Width, int Height)//设置ROI，注意宽度不超过1280，长度不超过1024
{
    GX_STATUS status;
    double exposure_time;
    int nOffsetX = (1280 - Width)/2;
    int nOffsetY = (1024 - Height)/2;
    status = GXSetInt(hDevice, GX_INT_WIDTH, Width);
    status = GXSetInt(hDevice, GX_INT_HEIGHT, Height);
    status = GXSetInt(hDevice, GX_INT_OFFSET_X, nOffsetX);
    status = GXSetInt(hDevice, GX_INT_OFFSET_Y, nOffsetY);
    return exposure_time;
}
