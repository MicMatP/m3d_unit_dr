#ifndef TYPE_SERIALIZATION_HPP
#define TYPE_SERIALIZATION_HPP
#include "m3d_driver_lib_export.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "3dUnitDriver.hpp"
using boost::property_tree::ptree;
namespace m3d
{
    class M3D_DRIVER_LIB_EXPORT typeSerialization
    {
    public:

        static void serialize(boost::property_tree::ptree &pt,m3d::rawPointcloud &v, std::string id);
        static void deserialize(boost::property_tree::ptree &pt, m3d::rawPointcloud &v, std::string id);

        static void serialize(boost::property_tree::ptree &pt, lms_channel &m, std::string id);
        static void deserialize(boost::property_tree::ptree &pt, lms_channel &m, std::string id);

        static void deserialize(boost::property_tree::ptree &pt, glm::mat4 &m, std::string id);
        static void serialize(boost::property_tree::ptree &pt, glm::mat4 &m, std::string id);

    };
};
#endif
