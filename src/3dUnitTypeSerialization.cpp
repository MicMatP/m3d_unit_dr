#include "3dUnitTypeSerialization.hpp"
#include <boost/foreach.hpp>
#include "logger.hpp"
#include <boost/optional/optional.hpp>

using namespace m3d;


void typeSerialization::serialize(boost::property_tree::ptree &pt, m3d::rawPointcloud &v, std::string id)
{
    ptree p;

    p.put("__type", "rawPointcloud");

    for (int i=0; i < v.ranges.size(); i++)
    {
        ptree profile;


        profile.put("angle", v.angles[i]);

        for (int j=0; j <v.ranges[i].echoes.size(); j++)
        {
            lms_channel *ch =&(v.ranges[i].echoes[j]);
            if (ch->data.size()>0)serialize(profile, *ch, "ECHO");
        }

        for (int j=0; j <v.ranges[i].rssis.size(); j++)
        {
            lms_channel *ch =&(v.ranges[i].rssis[j]);
            if (ch->data.size()>0)serialize(profile, *ch, "RSSI");
        }

        p.add_child("profile", profile);
    }
    pt.add_child(id, p);
}
void typeSerialization::serialize(boost::property_tree::ptree &pt, lms_channel &m, std::string id)
{


    ///std::string contents;
    ///float scallingFactor;
    ///float scallingOffset;
    ///float startAngle;
    ///float angStepWidth;
    ///int numberOfData;
    ///std::vector<int>data;
    ptree p;
    p.put("__type", "lms_channel");
    p.put ("id", id);
    p.put ("contents", m.contents);
    p.put ("scallingOffset", m.scallingOffset);
    p.put ("scallingFactor", m.scallingFactor);
    p.put ("angStepWidth", m.angStepWidth);
    p.put ("startAngle", m.startAngle);
    p.put ("numberOfData", m.numberOfData);
    std::stringstream ss;
    for (int i=0; i< m.data.size();i++)
    {
        ss<<m.data[i]<<'\t';
    }
    p.add("data", ss.str());
    pt.add_child(id, p);
}

void typeSerialization::deserialize(boost::property_tree::ptree &pt, m3d::rawPointcloud &v, std::string id)
{
    m3d::rawPointcloud m_raw;
    boost::property_tree::ptree pLocal = pt.get_child(id);
    std::string type = pLocal.get<std::string>("__type");
    if (type.compare("rawPointcloud")!=0) throw ("bad type");
    LOG_INFO("type ok");
    for(boost::property_tree::ptree::iterator iter = pLocal.begin(); iter != pLocal.end(); iter++)
    {
        boost::property_tree::ptree profileLocal = iter->second;
        if (iter->first.compare("profile")!= 0) continue;
        float angle = profileLocal.get("angle", -1000.0f);
        lms_measurement lm;
        lms_channel dist;
        lms_channel rssi;
        deserialize(profileLocal, dist, "ECHO");
        deserialize(profileLocal, rssi, "RSSI");

        lm.echoes.push_back(dist);
        lm.rssis.push_back(rssi);
        if (angle != -1000.0f)
        {
            m_raw.ranges.push_back(lm);
            m_raw.angles.push_back(angle);
        }
    }
    v= m_raw;
    LOG_INFO("Number of profiles "<<m_raw.angles.size());
}
void typeSerialization::deserialize(boost::property_tree::ptree &pt, lms_channel &m, std::string id)
{
    lms_channel my_channel;
    boost::optional<boost::property_tree::ptree&> pLocalOpt = pt.get_child_optional(id);
    if (!pLocalOpt)
    {
        LOG_WARN("cannot find node " << id);
        return;
    }
    boost::property_tree::ptree pLocal = pLocalOpt.get();
    std::string type = pLocal.get<std::string>("__type");
    if (type.compare("lms_channel")!=0) throw ("bad type");
    my_channel.contents = pLocal.get<std::string>("contents");
    my_channel.scallingOffset = pLocal.get<float>("scallingOffset");
    my_channel.scallingFactor = pLocal.get<float>("scallingFactor");
    my_channel.angStepWidth = pLocal.get<float>("angStepWidth");
    my_channel.startAngle = pLocal.get<float>("startAngle");
    my_channel.numberOfData = pLocal.get<float>("numberOfData");

    std::string data = pLocal.get<std::string>("data");
    std::stringstream ss(data);
    while (!ss.eof())
    {
        float d;
        ss>>d;
        my_channel.data.push_back(d);
    }
    m=my_channel;

}

void typeSerialization::deserialize(boost::property_tree::ptree &pt, glm::mat4 &m, std::string id)
{
    LOG_INFO("reading matrix");
    boost::property_tree::ptree pLocal = pt.get_child(id);
    std::string type = pLocal.get<std::string>("__type");
    if (type.compare("Mat4")!=0) throw ("bad type");
    std::string method = pLocal.get("__method","matrix");
    if (method.compare("matrix") ==0)
    {
        std::string data  =  pLocal.get<std::string>("data");
        std::stringstream ss(data);
        ss>>m[0][0]>>m[0][1]>>m[0][2]>>m[0][3];
        ss>>m[1][0]>>m[1][1]>>m[1][2]>>m[1][3];
        ss>>m[2][0]>>m[2][1]>>m[2][2]>>m[2][3];
        ss>>m[3][0]>>m[3][1]>>m[3][2]>>m[3][3];
    }
}

void typeSerialization::serialize(boost::property_tree::ptree &pt, glm::mat4 &m, std::string id)
{
    boost::property_tree::ptree pLocal;

    pLocal.add("__type", "Mat4");
    pLocal.add("__method", "matrix");
    std::stringstream ss;
    ss<<m[0][0]<<"\t"<<m[0][1]<<"\t"<<m[0][2]<<"\t"<<m[0][3]<<"\t";
    ss<<m[1][0]<<"\t"<<m[1][1]<<"\t"<<m[1][2]<<"\t"<<m[1][3]<<"\t";
    ss<<m[2][0]<<"\t"<<m[2][1]<<"\t"<<m[2][2]<<"\t"<<m[2][3]<<"\t";
    ss<<m[3][0]<<"\t"<<m[3][1]<<"\t"<<m[3][2]<<"\t"<<m[3][3]<<"\t";
    pLocal.add("data", ss.str());
    pt.add_child(id, pLocal);
}
