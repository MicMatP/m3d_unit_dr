#include <3dUnitDriver.hpp>
#include <3dUnitTypeSerialization.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void transferPc(m3d::rawPointcloud &raw, m3d::pointcloud &normalPc, m3d::_3dUnitConfig &cfg)
{
	for (int i=0; i< raw.angles.size(); i++)
	{

		float ang = raw.angles[i];

		if (ang !=-1)
		{
			glm::mat4 affine3Dunit = glm::rotate(glm::mat4(1.0f), cfg.angularOffsetRotLaser+ang, glm::vec3(0.0f, 0.0f, 1.0f));


			auto profile = raw.ranges.begin()+i;
			for (int i =0; i <profile->echoes[0].data.size(); i++)
			{

				//float lasAng = float(1.0*i *(lit->profile.echoes[0].angStepWidth)  -135.0f);
				float lasAng = float(1.0*i *(profile->echoes[0].angStepWidth)  - profile->echoes[0].startAngle);

				float d = profile->echoes[0].data[i];
				glm::vec4 in (d, 0.0, 0.0f, 1.0f);
				glm::mat4 affineLaser = glm::rotate(glm::mat4(1.0f), cfg.angularOffsetUnitLaser+glm::radians(lasAng),glm::vec3(0.0f, 0.0f, 1.0f));
				glm::mat4 calib = cfg.calibMatrix;
				glm::mat4 cor = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f));

				//glm::mat4 dAffine = glm::matrixCompMult(affineLaser, affine);
				glm::vec4 out =affine3Dunit* cor* calib* affineLaser * in;
				normalPc.data.push_back(glm::vec3(out.x, out.y,out.z));		
				if (profile->rssis.size()>0)normalPc.intensity.push_back(profile->rssis[0].data[i]);
			}
		}
	}
}

int main()
{
	using boost::property_tree::ptree;
	ptree pt;	
	std::cout <<"opening raw file \n";
	std::string fn  ="scan20150221T034434.meas";
	read_xml(fn, pt);
	m3d::rawPointcloud raw;
	m3d::typeSerialization::deserialize(pt,raw,"raw1");
	m3d::pointcloud normalPc;

	std::cout <<"opening 3dunit cfg file \n";
	m3d::_3dUnitConfig cfg;
	cfg.readConfigFromXML("3dUnitCfg.xml");
	std::cout <<"opening transfering pc \n";
	transferPc (raw, normalPc, cfg);
	m3d::typeSerialization::saveTXT(fn+".txt", normalPc);
}