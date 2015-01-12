#include "3dUnitDriver.hpp"
#include "encoder_driver.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <boost/log/trivial.hpp>
#define M_PI 3.14159265358979323846

namespace logging = boost::log;
	/// spawn everything - starts thread for lms, 3dunit, and synchronizer
	void _3dUnitDriver::initialize()
	{
		newSpeed =-1.0f;
		logging::core::get()->set_filter
		(
			logging::trivial::severity >= logging::trivial::info
		);

		_done = false;
		BOOST_LOG_TRIVIAL(debug) << "initializing _3dUnitDriver";
		lmsThread  =  boost::thread(boost::bind(&_3dUnitDriver::laserThreadWorker, this));
		encThread  =  boost::thread(boost::bind(&_3dUnitDriver::encoderWorker, this));
		collectorThread =  boost::thread(boost::bind(&_3dUnitDriver::combineThread, this));
		applyPriority(&lmsThread, ABOVE_NORMAL);
		applyPriority(&encThread, ABOVE_NORMAL);
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	}

	void _3dUnitDriver::deinitialize()
	{
		_done = true;
		BOOST_LOG_TRIVIAL(info)<<"waiting for joining threads";
		lmsThread.join();
		encThread.join();
		collectorThread.join();

	}

	_3dUnitDriver::_3dUnitDriver()
	{
		//LMS.debug();
		lmsIp ="192.168.0.201";
		unitIp="192.168.0.150";
		newSpeed =-1.0f;
		collectingPointcloud=false;
		_newPointCloud=false;
	}

	
	void _3dUnitDriver::encoderWorker()
	{
		BOOST_LOG_TRIVIAL(info)<<"enc thread started";
		ENC.connect_to_m3d(unitIp);
		ENC.setSpeed(30);
		while (!_done)
		{
			if (newSpeed !=-1.0f)
			{
				if (ENC.setSpeed(1*newSpeed))	newSpeed =-1;
			}
			bool isAngle =false;
			double angle = ENC.getAngle(isAngle);
			if (isAngle)
			{
				encoderMeasurment m;
				
				boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
				
				m.first = now;
				m.second =angle;
				BOOST_LOG_TRIVIAL(debug) <<"angle:"<< m.second<<"\n";
				encMeasurmentLock.lock();
				curentAngle = m.second;
					encMeasurmentBuffer.push_back(m);
					if(encMeasurmentBuffer.size()> 10) encMeasurmentBuffer.pop_back();
				encMeasurmentLock.unlock();
				boost::this_thread::sleep(boost::posix_time::millisec(15));

			}
			
			boost::this_thread::sleep(boost::posix_time::millisec(3));
		}
		ENC.setSpeed(0);
		boost::this_thread::sleep(boost::posix_time::millisec(300));
		BOOST_LOG_TRIVIAL(info)<<"enc thread ended";
	}

	void _3dUnitDriver::laserThreadWorker()
	{
		BOOST_LOG_TRIVIAL(debug)<<"lms thread started";
	    
		LMS.connectToLaser(lmsIp);
		LMS.requestContinousScan();
		
		while(!_done)
		{
			bool isMeasurment = false;
			LMS.readData(isMeasurment);
			if (isMeasurment &&!LMS.currentMessage.echoes.empty())
			{
				boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
				
				
				
				profileWithAngle m;
				m.encoder = abs(curentAngle);
				m.profile =LMS.currentMessage;
			
				laserMeasurmentsLock.lock();
				readyData.push_back(m);
				laserMeasurmentsLock.unlock();
				boost::this_thread::sleep(boost::posix_time::millisec(10));
				
				
			}
	
			
		
			
		}
		LMS.disconnet();
		BOOST_LOG_TRIVIAL(info)<<"lms thread ended";
	}

void _3dUnitDriver::getPointCloud(pointcloud &pc)
{
	pointcloudLock.lock();
	pc.data = lastPointCloud.data;
	pc.intensity = lastPointCloud.intensity;

	pointcloudLock.unlock();
}

void _3dUnitDriver::combineThread()
{
	//std::ofstream fileD;
	//fileD.open("debug.asc");
	while (!_done)
	{
		if (readyData.size()< 50)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(100));
			continue;
		}
	
		std::vector<glm::vec4> pointcloud;
		std::vector<profileWithAngle> copyProfiles;

		laserMeasurmentsLock.lock();
		copyProfiles = readyData;
		readyData.clear();
		laserMeasurmentsLock.unlock();
		
		for (std::vector<profileWithAngle>::iterator lit = copyProfiles.begin(); lit != copyProfiles.end(); lit++)
		{
			
			
			float ang = lit->encoder;
			
			if (ang !=-1)
			{
				glm::mat4 affine3Dunit = glm::rotate(glm::mat4(1.0f), ang, glm::vec3(0.0f, 0.0f, 1.0f));
				
				
				for (int i =0; i < lit->profile.echoes[0].data.size(); i++)
				{

					float lasAng = 1.0*i *(lit->profile.echoes[0].angStepWidth)  -135.0f;
					float d = lit->profile.echoes[0].data[i];
					glm::vec4 in (d, 0.0, 0.0f, 1.0f);
					glm::mat4 affineLaser = glm::rotate(glm::mat4(1.0f), glm::radians(lasAng),glm::vec3(0.0f, 0.0f, 1.0f));
					glm::mat4 calib = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -50.0f));
					glm::mat4 cor = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f));

					//glm::mat4 dAffine = glm::matrixCompMult(affineLaser, affine);
					glm::vec4 out =affine3Dunit* cor* calib* affineLaser * in;
					collectingPointCloud.data.push_back(glm::vec3(out.x, out.y,out.z));		
					if (lit->profile.rssis.size()>0)collectingPointCloud.intensity.push_back( lit->profile.rssis[0].data[i]);
				}
					
				float dAngle = abs(lit->encoder-lastAngleCollection);
				
				if (dAngle > 1*M_PI || (dAngle!=dAngle)) dAngle=0;
				//BOOST_LOG_TRIVIAL(info)  <<lastAngleCollection <<"\t"<<curentAngle<<"\t"<<dAngle<<"\t"<<angleCollection<< "\n";
				
				angleCollection=angleCollection+dAngle;


				angleCollection = angleCollection+dAngle;
				//BOOST_LOG_TRIVIAL(trace)<<angleCollection;
				if (abs(angleCollection) > 2.2* M_PI)
				{
					BOOST_LOG_TRIVIAL(info) <<"get angle :"<<angleCollection;
					angleCollection = 0.0f;
					
					pointcloudLock.lock();
					
					{
						lastPointCloud.data = collectingPointCloud.data;
						lastPointCloud.intensity = collectingPointCloud.intensity;
						collectingPointCloud.data.clear();
						collectingPointCloud.intensity.clear();
					}
					
					pointcloudLock.unlock();
					_newPointCloud = true;
					if(!scanCallback.empty()) scanCallback();
				}

				lastAngleCollection =  lit->encoder;

				
			}
		}
	}
	BOOST_LOG_TRIVIAL(info)<<"combine thread ended";
		
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

float _3dUnitDriver::getNearestAngle(boost::posix_time::ptime timeStamp)
{
	///@todo vector is nearly sorted - maybe optimalisation!!
	///@todo maybe better is map for measurments;
	float angle = -1;
    long long int maxTimeD =10;//msec
    long long int timeAcc =2; //msec
    long long int minimal_dTime =maxTimeD;
	for (std::vector<encoderMeasurment>::iterator it = encMeasurmentBuffer.begin(); it!= encMeasurmentBuffer.end(); it++)
	{
        long long int timeD = (it->first-timeStamp).total_milliseconds();
		if (abs(timeD) < minimal_dTime)
		{
			angle = it->second;
			minimal_dTime= abs(timeD);

		}
	}
	return angle;
}
