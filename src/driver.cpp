#include "3dUnitDriver.hpp"



int main(int argc, char **argv)
{


//    ros::init(argc, argv, "lms_mini_driver");
//    ros::NodeHandle n("~");
//    ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("laserScan",1);

    std::string ip = "192.168.0.201";

	_3dUnitDriver d;
	d.initialize();
	d.setSpeed(25);
	while (1);
	//d.deinitialize();
    return 0;
}
