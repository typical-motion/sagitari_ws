#ifndef _GET_FRAM_H
#define _GET_FRAM_H

#include <iostream>

using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

#include <arpa/inet.h> //used by linux

#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/StreamSource.h"
#include "GenICam/GigE/GigECamera.h"
#include "GenICam/GigE/GigEInterface.h"
#include "Infra/PrintLog.h"
#include "StreamRetrieve.h"
#include "Memory/SharedPtr.h"
#include <signal.h>

#include "Media/ImageConvert.h"
#include "GenICam/Frame.h"

#include "GenICam/ImageFormatControl.h"
using namespace Dahua::GenICam;
using namespace Dahua::Infra;

IStreamSourcePtr &get_connect_with_camare(ICameraPtr &cameraSptr);
bool disconnect_fram(CSystem &systemObj ,ICameraPtr &cameraSptr,IStreamSourcePtr & StreamSourcePtr);
int32_t setROI(ICameraPtr& cameraSptr, int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight);
int32_t setResolution(ICameraPtr& cameraSptr, int nWidth, int nHeight);


#endif
