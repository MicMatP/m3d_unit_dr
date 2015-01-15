#include "encoder_driver.hpp"
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#define M_PI 3.14159265358979323846
#include "logger.hpp"
void driver_encoder::connect_to_m3d(std::string IP)
{
	host = IP;
	std::string port ="10001";
        tcp::resolver resolver(io_service);
	tcp::resolver::query query(host.c_str(), port.c_str());
   	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
 	tcp::resolver::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
	while(error && endpoint_iterator != end){
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error) throw boost::system::system_error(error);
   bool t;
        getEncoderRes(t);
		LOG_INFO("m3d encoder res:"<< encRes);
}


bool driver_encoder::writeParam(int paramNo, int subindex, int paramValue)
{
    boost::system::error_code ignored_error;

    boost::system::error_code error;

    std::stringstream sstel;
    sstel<< "sp ";
    sstel<<std::hex<<paramNo;
    sstel<<"h.";
    sstel<<std::hex<<subindex;
    sstel<<"h ";
    sstel<<std::dec<<paramValue<<"\n";
	//BOOST_LOG_TRIVIAL(trace) <<"seting param " << sstel.str();
    boost::asio::write(socket, boost::asio::buffer(sstel.str()), boost::asio::transfer_all(), ignored_error);
    //boost::this_thread::sleep( boost::posix_time::millisec(20) );


    int len = socket.read_some(boost::asio::buffer(buf), error);

    if (error == boost::asio::error::eof)
        return false ; // Connection closed cleanly by peer.
    else if (error)
        throw boost::system::system_error(error); // Some other error.

    //BOOST_LOG_TRIVIAL(trace) <<"recived from m3d ", std::string(buf.begin(), buf.begin()+len);
    return true;
}

bool driver_encoder::getParam (int paramNo, int subindex, int &paramValue)
{

    boost::system::error_code ignored_error;

    boost::system::error_code error;

    std::stringstream sstel;
    sstel<< "gp ";
    sstel<<std::hex<<paramNo;
    sstel<<"h.";
    sstel<<std::hex<<subindex;
    sstel<<"h\n";
    //std::cout <<"getting param %s"<< sstel.str().c_str();
    boost::asio::write(socket, boost::asio::buffer(sstel.str()), boost::asio::transfer_all(), ignored_error);
    boost::this_thread::sleep(boost::posix_time::millisec(15));


    int len = socket.read_some(boost::asio::buffer(buf), error);

    if (error == boost::asio::error::eof)
        return false ; // Connection closed cleanly by peer.
    else if (error)
        throw boost::system::system_error(error); // Some other error.

    std::string data = std::string(buf.begin(), buf.begin()+len).c_str();


    std::vector<std::string> strs;
    boost::split(strs,data,boost::is_any_of(" "));

    //std::cout<<"recived from m3d " <<std::string(buf.begin(), buf.begin()+len);

    if (strs.size()!=4) return false;



    try {
        paramValue = boost::lexical_cast<int>(strs[2]);
    }
    catch(boost::bad_lexical_cast e)
    {
         std::cout<<"recived from m3d [BAD LEXICAL CAST] " <<std::string(buf.begin(), buf.begin()+len);
        return false;
    }
    //BOOST_LOG_TRIVIAL(trace) << "Value: ", paramValue;

    return true;
}

driver_encoder::driver_encoder()
	:socket(io_service)
{
}
bool driver_encoder::setPosition (float position, int speed, int relative)
{


		LOG_INFO("Setting new position");

        bool isOk =false;

        //pos mode
        isOk = writeParam(0x3003, 0x0, 7);
        if (!isOk) return false;
        //speed
        isOk = writeParam(0x3000,0x10, speed);
        if (!isOk) return false;
        //position
        position=static_cast<float>((position/(2*M_PI))*encRes);
        writeParam(0x3000,0x11, (int)position);
        if (!isOk) return false;
        //stop!
        writeParam(0x3000,0x1, 0);
        if (!isOk) return false;
        //start!

        if (relative) writeParam(0x3000,0x1, 51);
        if (!relative) writeParam(0x3000,0x1, 52);
        if (!isOk) return false;

    lastMode = POS;
}

float driver_encoder::getAngle(bool & isOk)
{
    int value;
    if (!getParam(0x396A, 0x0, value))
    {
        isOk =false ;
        return -1.0f;
    }
	isOk=true;
    value = value % encRes;
    float ret = -2*M_PI*value/encRes;
    return ret;
}

float driver_encoder::geVoltage(bool & isOk)
{
    int value;
    if (!getParam(0x3962, 0x0, value))
    {
        isOk =false ;
        return -1.0f;
    }
    encRes = value;
}
int driver_encoder::getEncoderRes(bool & isOk)
{
    int value;
    if (!getParam(0x3962, 0x0, value))
    {
        isOk =false ;
        return -1.0f;
    }
    encRes = 4*value;
	return encRes;
}
bool driver_encoder::setSpeed(int speed)
{
    LOG_INFO("seting speed to :" <<speed);

    bool isOk =false;
    //vel() mode
    isOk = writeParam(0x3003, 0x0, 3);
    if (!isOk) return false;
    //speed
    isOk = writeParam(0x3000,0x10, speed);
    if (!isOk) return false;
    //position
    //stop!
    writeParam(0x3000,0x1, 0);
    if (!isOk) return false;
    //start!

    writeParam(0x3000,0x1, 49);
    if (!isOk) return false;
	return true;
}
