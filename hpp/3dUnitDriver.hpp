#ifndef _UNIT_DRIVER_HPP
#define _UNIT_DRIVER_HPP

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>
#include <glm/glm.hpp>
#include "lms_mini_lib.hpp"

#include "encoder_driver.hpp"

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

struct pointcloud
{
	std::vector<glm::vec3> data;
	std::vector<float> intensity;
};

typedef std::pair<boost::posix_time::ptime, lms_measurement> laserMeasurment;
typedef std::pair<boost::posix_time::ptime, float> encoderMeasurment;

struct unitMeasurment
{
	std::vector<glm::vec3> points;
	std::vector<float> intensities;
	float actualAngle;
	boost::posix_time::ptime timestamp;
};

struct profileWithAngle
{
	lms_measurement profile;
	float encoder;
};

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

	///sets rotation speed;
	inline void setSpeed(float v)
	{
		newSpeed =v;
	}

	///sets a calibrating matrix
	inline void setMatrixCalibMatrix(glm::mat4 m)
	{
		laserCalibrationMatrix =m;
	}
	///request pointcloud
	inline void requestPointcloud()
	{
		collectingPointcloud =true;
		angleCollection=0;
		lastAngleCollection=curentAngle;
	}

	///wait for pointcloud (blocking)
	inline void waitForPointCloud()
	{
		while (_newPointCloud == false)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(100));
		}
		_newPointCloud=false;
		return;
	}
	/// get pointcloud
	void getPointCloud(pointcloud &pc);
private:
	///callback for laser thread

	float getNearestAngle(boost::posix_time::ptime timeStamp);
	void laserThreadWorker();
	void encoderWorker();
	void combineThread();

	/// rotating laser socket
	lms_socket LMS;
	/// encoder driver
	driver_encoder ENC;
	/// thread for collecting data from laser
	boost::thread lmsThread;
	boost::thread encThread;
	boost::thread collectorThread;
	bool _done ;
	std::string lmsIp;
	std::string unitIp;


	//buffer of measurments for m3dunit
	std::vector<encoderMeasurment> encMeasurmentBuffer;
	std::vector<profileWithAngle> readyData;
	float curentAngle;
	boost::mutex laserMeasurmentsLock;
	boost::mutex encMeasurmentLock;
	boost::mutex pointcloudLock;
	///actual collecting pointcloud
	pointcloud collectingPointCloud;
	///last measured pointcloud
	pointcloud lastPointCloud;

	glm::mat4 laserCalibrationMatrix;
	// new requested speed;
	float newSpeed;
	
	float angleCollection;
	float lastAngleCollection;
	bool collectingPointcloud;
	bool _newPointCloud;
};



#endif
