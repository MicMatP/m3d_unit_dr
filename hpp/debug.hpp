#ifndef _UNIT_DEBUG_HPP
#define _UNIT_DEBUG_HPP

#include <iostream>
#define _3D_DEBUG_LVL_DEBUG 0xff
#define _3D_DEBUG_LVL_INFO 0xfe
#define _3D_DEBUG_LVL_WARN 0xfd


///
#define _3D_COMP_DBGLEEVEL 0xff

#define _3D_DEBUG_LOG_TO_CONSOLE
#define _3D_DEBUG_LOG_TO_FILE

/// current logger level
extern unsigned  char _logLevel;



inline void _log_debug(const char *fmt, ...)
{
	if (_logLevel<_3D_DEBUG_LVL_DEBUG) return;
	
#ifdef _3D_DEBUG_LOG_TO_CONSOLE

	#ifdef _WIN32	
		char buffer[100];
		sprintf_s (buffer, 100,  fmt);
		std::cout<<buffer<<"\n";
	#elif __linux__
		char buffer[50];
		snprintf (buffer,  fmt);
		std::cout<<buffer<<"\n";
	#endif
#endif
}




inline void _log_info(const char *fmt, ...)
{

if (_logLevel<_3D_DEBUG_LVL_INFO) return;
#ifdef _3D_DEBUG_LOG_TO_CONSOLE

	#ifdef _WIN32	
		char buffer[50];
		sprintf_s (buffer,  fmt);
		std::cout<<buffer<<"\n";
	#elif __linux__
		char buffer[50];
		snprintf (buffer,  fmt);
		std::cout<<buffer<<"\n";
	#endif
#endif


}
inline void _log_warn(const char *fmt, ...)
{
	if (_logLevel<_3D_DEBUG_LVL_WARN) return;
#ifdef _3D_DEBUG_LOG_TO_CONSOLE

	#ifdef _WIN32	
		char buffer[50];
		sprintf_s (buffer,  fmt);
		std::cout<<buffer<<"\n";
	#elif __linux__
		char buffer[50];
		snprintf (buffer,  fmt);
		std::cout<<buffer<<"\n";
	#endif
#endif
}
#endif