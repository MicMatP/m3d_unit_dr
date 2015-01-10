#include "3dUnitDriver.hpp"


	/// spawn everything - starts thread for lms, 3dunit, and synchronizer
	void _3dUnitDriver::initialize()
	{
		_done = false;
		_log_info("initializing _3dUnitDriver");
		lmsThread  =  boost::thread(boost::bind(&_3dUnitDriver::laserThreadWorker, this));
		applyPriority(&lmsThread, HIGH);
	}

	void _3dUnitDriver::deinitialize()
	{
		_done = false;

	}

	_3dUnitDriver::_3dUnitDriver()
	{
		//LMS.debug();
		lmsIp ="192.168.0.201";
		lmsThread.join();
	}

	void _3dUnitDriver::laserThreadWorker()
	{
		_log_info("lms thread started");
	    
		LMS.connectToLaser(lmsIp);
		LMS.requestContinousScan();
		
		while(!_done)
		{
			bool isMeasurment = false;
			LMS.readData(isMeasurment);
			if (isMeasurment &&!LMS.currentMessage.echoes.empty())
			{
				boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
				laserMeasurment m;
				m.first = now;
				m.second = LMS.currentMessage;
				std::cout <<"measurment"<< m.second.echoes[0].numberOfData<<"\n";
				boost::this_thread::sleep(boost::posix_time::millisec(10));

				laserMeasurmentsLock.lock();
				{
					laserMeasurmentBuffer.push_back(m);
					if(laserMeasurmentBuffer.size()> 150) laserMeasurmentBuffer.pop_back();
				}
				laserMeasurmentsLock.unlock();
				
			}
			boost::this_thread::sleep(boost::posix_time::millisec(5));
		}

		LMS.disconnet();
	}


void applyPriority(boost::thread* m_pThread,  threadPriority priority)
{
// some native WINAPI ugh!
#ifdef _WIN32
    if (!m_pThread)
    	return;

    BOOL res;
    HANDLE th = m_pThread->native_handle();
    switch (priority)
    {
    case REALTIME		: res = SetThreadPriority(th, THREAD_PRIORITY_TIME_CRITICAL);	break;
    case HIGH			: res = SetThreadPriority(th, THREAD_PRIORITY_HIGHEST);			break;
    case ABOVE_NORMAL	: res = SetThreadPriority(th, THREAD_PRIORITY_ABOVE_NORMAL);	break;
    case NORMAL			: res = SetThreadPriority(th, THREAD_PRIORITY_NORMAL);			break;
    case BELOW_NORMAL	: res = SetThreadPriority(th, THREAD_PRIORITY_BELOW_NORMAL);	break;
    case IDLE			: res = SetThreadPriority(th, THREAD_PRIORITY_LOWEST);			break;
    }
#else
	std::cerr<<"CANNOT SET THREAD PRIORITY ON THIS PLATFORM \n";
#endif
}
