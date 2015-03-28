#include <3dUnitDriver.hpp>
#include <3dUnitTypeSerialization.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "usage:\n";
		std::cout << argv[0] <<" rawMeasurmentInput Output cfgfile";
		return 1;
	}
	std::string fnIn;
	std::string fnOut;
	std::string fnCfg;

	if (argc == 4)
	{
		fnIn = argv[1];
		fnOut = argv[2];
		fnCfg = argv[3];
	}
	using boost::property_tree::ptree;
	ptree pt;	
	std::cout <<"opening raw file \n";

	read_xml(fnIn, pt);
	m3d::rawPointcloud raw;
	m3d::typeSerialization::deserialize(pt,raw,"raw1");

	std::cout <<"opening 3dunit cfg file \n";
	m3d::_3dUnitConfig cfg;
	cfg.readConfigFromXML(fnCfg);
	std::cout <<"opening transfering pc \n";
	m3d::pointcloud normalPc;

	m3d::transferPc (raw, normalPc, cfg);
	m3d::typeSerialization::saveTXT(fnOut, normalPc);
	return 0;
}