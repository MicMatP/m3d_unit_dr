#include "3dUnitTypeSerialization.hpp"

boost::property_tree::ptree m3d::typeSerialization::pt;

using namespace m3d;
//void typeSerialization::read(std::fileName);
void typeSerialization::write(std::fileName);


void typeSerialization::push(m3d::rawPointcloud &v, std::string id)
{
    ptree p = pt.add("rawPointCloud");
    p.put("id", id);

    for (int i=0; i < v.ranges; i++)
    {
        ptree profile = p.add("profile");
        profiele.put("angle", v.angles[i]);
        lms_channel *ch =v.ranges[i].echoes[0];
        profile.put ("lms_angStepWidth", ch->angStepWidth);
        profile.put ("lms_numberOfData", ch->numberOfData);
        profile.put ("lms_scallingFactor", ch->scallingFactor);
        profile.put ("lms_startAngle", ch->startAngle);
    }

}

void typeSerialization::get(m3d::rawPointcloud &v, std::string id)
{

}
