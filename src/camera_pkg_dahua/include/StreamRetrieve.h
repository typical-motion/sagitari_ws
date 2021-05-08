#include <Infra/Thread.h>
#include <GenICam/StreamSource.h>

using namespace Dahua::GenICam;
using namespace Dahua::Infra;


class StreamRetrieve : public CThread
{
public:
	StreamRetrieve(IStreamSourcePtr& streamSptr);
	bool start();
	void stop();

private:
	void threadProc();
	bool m_isLoop;
	IStreamSourcePtr m_streamSptr;
};
