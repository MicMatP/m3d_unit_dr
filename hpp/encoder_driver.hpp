#ifndef _ENCODER_DRIVER_HPP
#define _ENCODER_DRIVER_HPP
#include "m3d_driver_lib_export.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>


using boost::asio::ip::tcp;


using namespace boost::asio;
using namespace boost::system;
//using boost::optional;


class M3D_DRIVER_LIB_EXPORT driver_encoder
{

    enum mode
    {
        VEL, POS
    };

public:
	driver_encoder();
    void connect_to_m3d(std::string IP);
	void disconnet();
    bool writeParam(int paramNo, int subindex, int paramValue);
    bool getParam (int paramNo, int subindex, int &paramValue);
    bool setPosition (float position, int speed, int relative);
    bool setSpeed(int speed);
    float getAngle()
    {
        bool t;
        float res=  getAngle(t);
        if (t) return res;
         return -1.0f;
    }

    float getAngle(bool & isOk);
    float geVoltage(bool & isOk);
    int getEncoderRes(bool & isOk);
private:
	boost::asio::io_service io_service;
	tcp::socket socket;
	std::string host;
	std::string incommingData;
    int encRes;
    mode lastMode;
	boost::array<char, 100> buf;
};
#endif