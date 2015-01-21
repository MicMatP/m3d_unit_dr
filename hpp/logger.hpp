#ifndef LOGGER_HPP
#define LOGGER_HPP
 
#define _PRINTOUT_DEBUG 4
#define _PRINTOUT_INFO 3
#define _PRINTOUT_WARN 2
#define _PRINTOUT_FATAL 1

#define _PRINTOUT_MUTE 0



int extern _____dLevel;


#define SET_DEBUGLVL(f) int _____dLevel=f

#define LOG_DEBUG(f) if(_____dLevel>=_PRINTOUT_DEBUG)std::cout<<"[DEBUG] "<<f<<std::endl

#define LOG_INFO(f) if(_____dLevel>=_PRINTOUT_INFO)std::cout<<"[INFO] "<<f<<std::endl

#define LOG_WARN(f) if(_____dLevel>=_PRINTOUT_WARN)std::cout<<"[WARN] " <<f<<std::endl

#define LOG_FATAL(f) if(_____dLevel>=_PRINTOUT_FATAL)std::cout<<"[FATAL] " <<f<<std::endl

#endif