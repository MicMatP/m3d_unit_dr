#include "3dUnitDriver.hpp"
#include <iostream>
#include <fstream>
#include <iostream>
//#define sync_read
#define async_read

m3d::_3dUnitDriver* d;


#ifndef sync_read
class example
{
public:
	example():i(0){};
	void asyncPointcloud()
	{
		std::cout<<"Got pointcloud !\n";
		std::ofstream pcfile;
		m3d::pointcloud pc;
		d->getPointCloud(pc);
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
private: 
	int i;
};
#endif

int main(int argc, char **argv)
{

	


//    ros::init(argc, argv, "lms_mini_driver");
//    ros::NodeHandle n("~");
//    ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("laserScan",1);

    std::string ip = "192.168.0.201";
	m3d::_3dUnitConfig cfg;
	cfg.readConfigFromXML("3dunitCfg.xml");
	d= (new m3d::_3dUnitDriver (cfg));
	d->initialize();
	d->setSpeed(8);
	d->requestPointcloud();
	int i=0;
#ifndef sync_read	
	example w;
	d->setCallbackPointCloud(boost::bind(&example::asyncPointcloud, &w));
#endif;

	
	while (1)
	{

#ifdef sync_read
		d->waitForPointCloud();
		std::cout<<"Got pointcloud !\n";
		std::ofstream pcfile;
		pointcloud pc;
		d->getPointCloud(pc);
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
#else
		
		boost::this_thread::sleep(boost::posix_time::millisec(100));
#endif
		if (std::cin.get() == 'n') break;
	}
	delete d;
	return 0;
}
