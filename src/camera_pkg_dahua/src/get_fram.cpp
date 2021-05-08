#include "get_fram.h"
//CSystem systemObj ;
static int32_t setGrabMode(ICameraPtr& cameraSptr, bool bContious)
{
    int32_t bRet;
    IAcquisitionControlPtr sptrAcquisitionControl = CSystem::getInstance().createAcquisitionControl(cameraSptr);
    if (NULL == sptrAcquisitionControl)
    {
        return -1;
    }

    CEnumNode enumNode = sptrAcquisitionControl->triggerSelector();
    bRet = enumNode.setValueBySymbol("FrameStart");
    if (false == bRet)
    {
        printf("set TriggerSelector fail.\n");
        return -1;
    }

    if (true == bContious)
    {
        enumNode = sptrAcquisitionControl->triggerMode();
        bRet = enumNode.setValueBySymbol("Off");
        if (false == bRet)
        {
            printf("set triggerMode fail.\n");
            return -1;
        }
    }
    else
    {
        enumNode = sptrAcquisitionControl->triggerMode();
        bRet = enumNode.setValueBySymbol("On");
        if (false == bRet)
        {
            printf("set triggerMode fail.\n");
            return -1;
        }

        /* ÉèÖÃ´¥·¢Ô´ÎªÈí´¥·¢£¨Ó²´¥·¢ÎªLine1£© */
        enumNode = sptrAcquisitionControl->triggerSource();
        bRet = enumNode.setValueBySymbol("Software");
        if (false == bRet)
        {
            printf("set triggerSource fail.\n");
            return -1;
        }
    }
    return 0;
}


static int32_t autoSetCameraIP(ICameraPtr& cameraSptr)
{
	IGigECameraPtr gigeCameraPtr = IGigECamera::getInstance(cameraSptr);
	if(NULL == gigeCameraPtr)
	{
		return -1;
	}

	//»ñÈ¡GigeÏà»úÏà¹ØÐÅÏ¢
	CString ip = gigeCameraPtr->getIpAddress();
	CString subnetMask = gigeCameraPtr->getSubnetMask();
	CString gateway = gigeCameraPtr->getGateway();
	CString macAddress = gigeCameraPtr->getMacAddress();
	printf("ip address is %s.\r\n", ip.c_str());
	printf("subnetMask is %s.\r\n", subnetMask.c_str());
	printf("gateway is %s.\r\n", gateway.c_str());
	printf("macAddress is %s.\r\n", macAddress.c_str());
	printf("\n");

	unsigned long devIpValue = ntohl(inet_addr(gigeCameraPtr->getIpAddress().c_str()));
	unsigned long devSubMaskValue = ntohl(inet_addr(gigeCameraPtr->getSubnetMask().c_str()));

	//»ñÈ¡¶ÔÓ¦½Ó¿ÚµÄÍø¿¨ÐÅÏ¢
	IGigEInterfacePtr gigeInterfaceSPtr = IGigEInterface::getInstance(cameraSptr);
	if(NULL == gigeInterfaceSPtr)
	{
		return -1;
	}

	CString interfaceIp = gigeInterfaceSPtr->getIpAddress();
	CString interfaceSubnetMask = gigeInterfaceSPtr->getSubnetMask();
	CString interfaceGateway = gigeInterfaceSPtr->getGateway();
	CString interfaceMacAddress = gigeInterfaceSPtr->getMacAddress();
	printf("ip address of interface  is %s.\r\n", interfaceIp.c_str());
	printf("subnetMask of interface is %s.\r\n", interfaceSubnetMask.c_str());
	printf("gateway of interface is %s.\r\n", interfaceGateway.c_str());
	printf("macAddress of interface is %s.\r\n", interfaceMacAddress.c_str());
	printf("\n");

	unsigned long InterfaceIpValue = ntohl(inet_addr(gigeInterfaceSPtr->getIpAddress().c_str()));
	unsigned long InterfaceSubMaskValue = ntohl(inet_addr(gigeInterfaceSPtr->getSubnetMask().c_str()));

	if( (devIpValue & devSubMaskValue) != (InterfaceIpValue & InterfaceSubMaskValue) )
	{
		//Éè±¸ÓëÍø¿¨²»ÔÚÍ¬Ò»Íø¶Î£¬Ç¿ÖÆÉèÖÃÉè±¸ÓëÍø¿¨ÔÚÍ¬Ò»Íø¶Î
		unsigned char newIPStr[20] = {0};

		while(1)
		{
			unsigned long newIpValue = rand() % 254 + 1; //1~254
			if(newIpValue != (InterfaceIpValue & 0xff))
			{
				newIpValue = (InterfaceIpValue & 0xffffff00) + newIpValue;
				struct in_addr   stInAddr;
				stInAddr.s_addr	= htonl(newIpValue);
				memcpy(newIPStr, inet_ntoa(stInAddr), strlen(inet_ntoa(stInAddr)));
				break;
			}
		}

		if(!gigeCameraPtr->forceIpAddress((const char*)newIPStr, gigeInterfaceSPtr->getSubnetMask().c_str(), gigeInterfaceSPtr->getGateway().c_str()))
		{
			printf("Set device ip failed.\n");
			return -1;
		}
	}

	return 0;
}

int32_t setResolution(ICameraPtr& cameraSptr, int nWidth, int nHeight)
{
    int32_t bRet;
    IImageFormatControlPtr sptrImageFormatControl = CSystem::getInstance().createImageFormatControl(cameraSptr);
    if (NULL == sptrImageFormatControl)
    {
        return -1;
    }

    CIntNode intNode = sptrImageFormatControl->width();
    bRet = intNode.setValue(nWidth);
    if (false == bRet)
    {
        printf("set width fail.\n");
        return -1;
    }

    intNode = sptrImageFormatControl->height();
    bRet = intNode.setValue(nHeight);
    if (false == bRet)
    {
        printf("set height fail.\n");
        return -1;
    }
    return 0;
}

/* 10¡¢»ñÈ¡´«¸ÐÆ÷²ÉÑùÂÊ */
static int32_t getResolution(ICameraPtr& cameraSptr, int64_t &nWidth, int64_t &nHeight)
{
    int32_t bRet;
    IImageFormatControlPtr sptrImageFormatControl = CSystem::getInstance().createImageFormatControl(cameraSptr);
    if (NULL == sptrImageFormatControl)
    {
        return -1;
    }

    CIntNode intNode = sptrImageFormatControl->width();
    bRet = intNode.getValue(nWidth);
    if (false == bRet)
    {
        printf("get width fail.\n");
        return -1;
    }

    intNode = sptrImageFormatControl->height();
    bRet = intNode.getValue(nHeight);
    if (false == bRet)
    {
        printf("get height fail.\n");
        return -1;
    }
    return 0;
}

/* ÉèÖÃbinning (Off X Y XY) */
static int32_t setBinning(ICameraPtr& cameraSptr)
{
    CEnumNodePtr ptrParam(new CEnumNode(cameraSptr, "Binning"));
    if (ptrParam)
    {
        if (false == ptrParam->isReadable())
        {
            printf("binning not support.\n");
            return -1;
        }

        if (false == ptrParam->setValueBySymbol("XY"))
        {
            printf("set Binning XY fail.\n");
            return -1;
        }

        if (false == ptrParam->setValueBySymbol("Off"))
        {
            printf("set Binning Off fail.\n");
            return -1;
        }
    }
    return 0;
}

/* 11¡¢»ñÈ¡´«¸ÐÆ÷×î´ó·Ö±çÂÊ */
int32_t getMaxResolution(ICameraPtr& cameraSptr, int64_t &nWidthMax, int64_t &nHeightMax)
{
    /* width */
    {
        CIntNodePtr ptrParam(new CIntNode(cameraSptr, "SensorWidth"));
        if (ptrParam)
        {
            if (false == ptrParam->getValue(nWidthMax))
            {
                printf("get WidthMax fail.\n");
                return -1;
            }
        }
    }

    /* height */
    {
        CIntNodePtr ptrParam(new CIntNode(cameraSptr, "SensorHeight"));
        if (ptrParam)
        {
            if (false == ptrParam->getValue(nWidthMax))
            {
                printf("get WidthMax fail.\n");
                return -1;
            }
        }
    }
    return 0;
}


int32_t setROI(ICameraPtr& cameraSptr, int64_t nX, int64_t nY, int64_t nWidth, int64_t nHeight)
{
    bool bRet;
    IImageFormatControlPtr sptrImageFormatControl = CSystem::getInstance().createImageFormatControl(cameraSptr);
    if (NULL == sptrImageFormatControl)
    {
        return -1;
    }

    /* width */
    CIntNode intNode = sptrImageFormatControl->width();
    bRet = intNode.setValue(nWidth);
    if (!bRet)
    {
        printf("set width fail.\n");
	return -1;
    }

    /* height */
    intNode = sptrImageFormatControl->height();
    bRet = intNode.setValue(nHeight);
    if (!bRet)
    {
        printf("set height fail.\n");
	return -1;
    }

    /* OffsetX */
    intNode = sptrImageFormatControl->offsetX();
    bRet = intNode.setValue(nX);
    if (!bRet)
    {
        printf("set offsetX fail.\n");
	return -1;
    }

    /* OffsetY */
    intNode = sptrImageFormatControl->offsetY();
    bRet = intNode.setValue(nY);
    if (!bRet)
    {
        printf("set offsetY fail.\n");
	return -1;
    }

    return 0;
}



IStreamSourcePtr &get_connect_with_camare(ICameraPtr &cameraSptr)
{
	CSystem &systemObj = CSystem::getInstance();
    TVector<ICameraPtr> vCameraPtrList;
    bool isDiscoverySuccess = systemObj.discovery(vCameraPtrList);
    if (!isDiscoverySuccess)
    {
        printf("discovery device fail.\n");
        exit(-1);
        //return 0;
    }

    if (vCameraPtrList.size() == 0)
    {
        printf("no devices.\n");
		exit(-1);
        //return 0;
    }
	
	// print camera info (index,Type,vendor name, model,serial number,DeviceUserID,IP Address)
	// ´òÓ¡Ïà»ú»ù±¾ÐÅÏ¢£¨ÐòºÅ,ÀàÐÍ,ÖÆÔìÉÌÐÅÏ¢,ÐÍºÅ,ÐòÁÐºÅ,ÓÃ»§×Ô¶¨ÒåID,IPµØÖ·£©
//	displayDeviceInfo(vCameraPtrList);
//	int cameraIndex = selectDevice(vCameraPtrList.size());
//	cameraSptr = vCameraPtrList[cameraIndex];
	
	cameraSptr = vCameraPtrList[0];//0,cameraindex
	/* GigEÏà»úÊ±£¬Á¬½ÓÇ°ÉèÖÃÏà»úIpÓëÍø¿¨´¦ÓÚÍ¬Ò»Íø¶ÎÉÏ */
	if( ICamera::typeGige == cameraSptr->getType())
	{
		if(autoSetCameraIP(cameraSptr) != 0)
		{
			printf("set camera Ip failed.\n");
		}
	}
	
    /* Á¬½ÓÏà»ú */
    if (!cameraSptr->connect())
    {
        printf("connect cameral failed.\n");
		exit(-1);
	}
	    
	IImageFormatControlPtr sptrFormatControl;
	sptrFormatControl = systemObj.createImageFormatControl(cameraSptr);
	CIntNode nodeWidth = sptrFormatControl -> width();
	nodeWidth.setValue(1024);
	CIntNode nodeHeight = sptrFormatControl -> height();
	nodeHeight.setValue(480);
	CIntNode nodeOffSetX = sptrFormatControl -> offsetX();
	nodeOffSetX.setValue(448);
	CIntNode nodeOffSetY = sptrFormatControl -> offsetY();
	nodeOffSetY.setValue(360);
	/* ÉèÖÃÏà»úÎªÁ¬ÐøÀ­Á÷Ä£Ê½ */
    
    setGrabMode(cameraSptr, true);
    static IStreamSourcePtr streamPtr = systemObj.createStreamSource(cameraSptr);
    IStreamSourcePtr &streamPtr_bac = streamPtr;
    if (NULL == streamPtr)
    {
        printf("create stream obj  fail.\r\n");
		exit(-1);
    }
//	while(1) {
	 /*  */
    bool isStartGrabbingSuccess = streamPtr->startGrabbing();
   
    if (!isStartGrabbingSuccess)
    {
        printf("StartGrabbing  fail.\n");
    }
    //printf("DEBUG1\n");
   //  printf("DEBUG\n");
  /*  int64_t nWidth, nHeight;
    setResolution(cameraSptr, 640, 480);
    getResolution(cameraSptr, nWidth, nHeight);

    setBinning(cameraSptr);

    getMaxResolution(cameraSptr, nWidth, nHeight);*/
     return streamPtr_bac;
}
int32_t setGainRaw(ICameraPtr& cameraSptr, double dGainRaw)
{
    bool bRet;
    IAnalogControlPtr sptrAnalogControl = CSystem::getInstance().createAnalogControl(cameraSptr);
    if (NULL == sptrAnalogControl)
    {
        return -1;
    }

    CDoubleNode doubleNode = sptrAnalogControl->gainRaw();
    bRet = doubleNode.setValue(dGainRaw);
    if (false == bRet)
    {
        printf("set gainRaw fail.\n");
        return -1;
    }
    return 0;
}
int32_t setBalanceRatio_Auto(ICameraPtr& cameraSptr)//自动白平衡
{
    bool bRet;
    IAnalogControlPtr sptrAnalogControl = CSystem::getInstance().createAnalogControl(cameraSptr);


    if (NULL == sptrAnalogControl)
    {
        return -1;
    }


    CEnumNode enumNode = sptrAnalogControl->balanceWhiteAuto();
    
    //打开自动白平衡
    if (false == enumNode.isReadable())
    {
        printf("balanceRatio not support.\n");
        return -1;
    }


    bRet = enumNode.setValueBySymbol("On");
    if (false == bRet)
    {
        printf("set balanceWhiteAuto On fail.\n");
        return -1;
    }
    return 0;
}

int32_t setBalanceRatio(ICameraPtr& cameraSptr, double dRedBalanceRatio, double dGreenBalanceRatio, double dBlueBalanceRatio)
{
    bool bRet;
    IAnalogControlPtr sptrAnalogControl = CSystem::getInstance().createAnalogControl(cameraSptr);
    if (NULL == sptrAnalogControl)
    {
        return -1;
    }
    /* 关闭自动白平衡 */
    CEnumNode enumNode = sptrAnalogControl->balanceWhiteAuto();
    if (false == enumNode.isReadable())
    {
        printf("balanceRatio not support.\n");
        return -1;
    }
    

    bRet = enumNode.setValueBySymbol("Off");
    if (false == bRet)
    {
        printf("set balanceWhiteAuto Off fail.\n");
        return -1;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Red");
    if (false == bRet)
    {
        printf("set red balanceRatioSelector fail.\n");
        return -1;
    }

    CDoubleNode doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dRedBalanceRatio);
    if (false == bRet)
    {
        printf("set red balanceRatio fail.\n");
        return -1;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Green");
    if (false == bRet)
    {
        printf("set green balanceRatioSelector fail.\n");
        return -1;
    }

    doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dGreenBalanceRatio);
    if (false == bRet)
    {
        printf("set green balanceRatio fail.\n");
        return -1;
    }

    enumNode = sptrAnalogControl->balanceRatioSelector();
    bRet = enumNode.setValueBySymbol("Blue");
    if (false == bRet)
    {
        printf("set blue balanceRatioSelector fail.\n");
        return -1;
    }

    doubleNode = sptrAnalogControl->balanceRatio();
    bRet = doubleNode.setValue(dBlueBalanceRatio);
    if (false == bRet)
    {
        printf("set blue balanceRatio fail.\n");
        return -1;
    }
    return 0;
}
int32_t setGamma(ICameraPtr& cameraSptr, double dGamma)
{
    bool bRet;
    IAnalogControlPtr sptrAnalogControl = CSystem::getInstance().createAnalogControl(cameraSptr);
    if (NULL == sptrAnalogControl)
    {
        return -1;
    }

    CDoubleNode doubleNode = sptrAnalogControl->gamma();
    bRet = doubleNode.setValue(dGamma);
    if (false == bRet)
    {
        printf("set gamma fail.\n");
        return -1;
    }
    return 0;
}
int32_t setExposureTime(ICameraPtr& cameraSptr, double dExposureTime, bool bAutoExposure = false)
{
    bool bRet;
    IAcquisitionControlPtr sptrAcquisitionControl = CSystem::getInstance().createAcquisitionControl(cameraSptr);
    if (NULL == sptrAcquisitionControl)
    {
        return -1;
    }

    if (bAutoExposure)
    {
        CEnumNode enumNode = sptrAcquisitionControl->exposureAuto();
        bRet = enumNode.setValueBySymbol("Continuous");
        if (false == bRet)
        {
            printf("set exposureAuto fail.\n");
            return -1;
        }
    }
    else
    {
        CEnumNode enumNode = sptrAcquisitionControl->exposureAuto();
        bRet = enumNode.setValueBySymbol("Off");
        if (false == bRet)
        {
            printf("set exposureAuto fail.\n");
            return -1;
        }

        CDoubleNode doubleNode = sptrAcquisitionControl->exposureTime();
        bRet = doubleNode.setValue(dExposureTime);
        if (false == bRet)
        {
            printf("set exposureTime fail.\n");
            return -1;
        }
    }
    return 0;
}

static void modifyCamralExposureTime(CSystem &systemObj, ICameraPtr& cameraSptr)
{
    IAcquisitionControlPtr sptrAcquisitionControl = systemObj.createAcquisitionControl(cameraSptr);
    if (NULL == sptrAcquisitionControl)
    {
        return;
    }

    double exposureTimeValue = 0.0;
    CDoubleNode exposureTime = sptrAcquisitionControl->exposureTime();

    exposureTime.getValue(exposureTimeValue);
    printf("before change ,exposureTime is %f. thread ID :%d\n", exposureTimeValue, CThread::getCurrentThreadID());

    exposureTime.setValue(exposureTimeValue + 2);
    exposureTime.getValue(exposureTimeValue);
    printf("after change ,exposureTime is %f. thread ID :%d\n", exposureTimeValue, CThread::getCurrentThreadID());
}



bool disconnect_fram(ICameraPtr &cameraSptr,IStreamSourcePtr & streamPtr)
{
	 streamPtr->stopGrabbing();
    /* ÐÞ¸ÄÏà»úÆØ¹âÊ±¼ä */
    //modifyCamralExposureTime(systemObj, cameraSptr);
    /* ¶Ï¿ªÏà»ú */
    if (!cameraSptr->disConnect())
    {
        printf("disConnect camera failed\n");
        return false;
    }
//    printf("disConnect successfully thread ID :%d\n", CThread::getCurrentThreadID());
    return true;
}
