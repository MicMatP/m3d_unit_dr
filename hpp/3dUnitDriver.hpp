#ifndef _UNIT_DRIVER_HPP
#define _UNIT_DRIVER_HPP
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>
#include "lms_mini_lib.hpp"
#include "debug.hpp"

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)


typedef std::pair<boost::posix_time::ptime, lms_measurement> laserMeasurment;
typedef std::pair<boost::posix_time::ptime, float> encoderMeasurment;



struct config
{
	std::string rotLaserIp;
	std::string _3dunitIp;

};


enum threadPriority {REALTIME, HIGH, ABOVE_NORMAL,NORMAL,BELOW_NORMAL,IDLE};
void extern applyPriority(boost::thread* m_pThread,  threadPriority priority);


class _3dUnitDriver
{
public:
	/// spawn everything - starts thread for lms, 3dunit, and synchronizer
	void initialize();

	void deinitialize();

	_3dUnitDriver();
private:
	///callback for laser thread
	void laserThreadWorker();


	/// rotating laser socket
	lms_socket LMS;
	
	/// thread for collecting data from laser
	boost::thread lmsThread;
	boost::thread _3dunitThread;
	boost::thread collectorThread;
	bool _done ;
	std::string lmsIp;
	//buffer of measurments for laser
	std::vector<laserMeasurment> laserMeasurmentBuffer;
	//buffer of measurments for m3dunit
	std::vector<encoderMeasurment> _3dUnitMeasurmentBuffer;

	boost::mutex laserMeasurmentsLock;
	boost::mutex _3dUnitMeasurmentLock;

};



#endif
