#include "3dUnitDriver.hpp"
#include <iostream>
#include <fstream>
#include <iostream>
//#define sync_read
#define async_read

m3d::_3dUnitDriver* d;

int main(int argc, char **argv)
{

	


	m3d::_3dUnitConfig cfg;
	cfg.readConfigFromXML("3dunitCfg.xml");
	d= (new m3d::_3dUnitDriver (cfg));
	d->initializeEncoderOnly();
	
	while (1)
	{
		std::cout <<"Current angle :"<<d->getCurrentAngle()<<"\n";
		//if (std::cin.get() == 'n') break;
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	}
	delete d;
	return 0;
}
