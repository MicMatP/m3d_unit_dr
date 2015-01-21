#ifndef TYPE_SERIALIZATION_HPP
#define TYPE_SERIALIZATION_HPP


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "3dUnitDriver.hpp"
using boost::property_tree::ptree;

class m3d::typeSerialization
{

    static void read(std::fileName);
    static void write(std::fileName);


    static void push(m3d::rawPointcloud &v, std::string id);

    static void get(m3d::rawPointcloud &v, std::string id);



private:
   static boost::property_tree::ptree pt;

};

#endif
