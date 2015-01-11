#include "3dUnitDriver.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{


//    ros::init(argc, argv, "lms_mini_driver");
//    ros::NodeHandle n("~");
//    ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("laserScan",1);

    std::string ip = "192.168.0.201";

	_3dUnitDriver d;
	d.initialize();
	d.setSpeed(8);
	d.requestPointcloud();
	int i=0;
	while (1)
	{
		d.waitForPointCloud();
		std::cout<<"weee pointcloud !\n";
		std::ofstream pcfile;
		pointcloud pc;
		d.getPointCloud(pc);
		char str[100];
		std::sprintf(str, "scan%d.asc", i++);
		std::cout <<"size:"<<pc.data.size() <<"writing pointcloud "<<str;
		pcfile.open(str);

		for (int k=0; k < pc.data.size(); k++)
		{
			float intensity = 0;
			if (pc.intensity.size()>k) intensity = pc.intensity[k];
			pcfile<<pc.data[k].x<<"\t"<<pc.data[k].y<<"\t"<<pc.data[k].z<<"\t"<<intensity<<"\n";
		}
		pcfile.close();

	}
	//d.deinitialize();
    return 0;
}
