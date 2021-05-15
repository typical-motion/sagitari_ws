#ifdef __unix__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif
#include "StreamRetrieve.h"
#include "GenICam/Frame.h"

StreamRetrieve::StreamRetrieve(IStreamSourcePtr& streamSptr)
	: CThread("streamRetrieve")
	, m_isLoop(false)
	, m_streamSptr(streamSptr)
{
	
}

bool StreamRetrieve::start()
{
	m_isLoop = true;
	return createThread();
}

void StreamRetrieve::stop()
{
	m_isLoop = false;
	m_streamSptr.reset();
}

void StreamRetrieve::threadProc()
{
	
	while (m_isLoop)
	{
		CFrame frame;

		//��ȡһ֡
		if (!m_streamSptr)
		{
			printf("m_streamPtr is NULL.\n");
			return;
		}
		bool isSuccess = m_streamSptr->getFrame(frame, 300);
		if (!isSuccess)
		{
			printf("getFrame  fail.\n");
			continue;
		}

		//�ж�֡����Ч��
		bool isValid = frame.valid();
		if (!isValid)
		{
			printf("frame is invalid!\n");
			continue;
		}

		//��ӡFrameID
		printf("get frame %lu successfully thread ID :%d\n", frame.getBlockId(), CThread::getCurrentThreadID());
	}

}


