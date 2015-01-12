cmake_minimum_required(VERSION 2.7)
include(GenerateExportHeader)
PROJECT(MANDALA_3dUnit)
#iF YOU DOES NOT HAVE LIBRARIES IN PATH, YOU CAN EASILY DEFINE ALL HERE
SET(BOOST_ROOT H:/Libs/boost_1_57_0vs2012x64)
SET(BOOST_LIBRARYDIR H:/Libs/boost_1_57_0vs2012x64/lib64-msvc-10.0)

SET(PROJECT_NAME MANDALA_3dUnit)
IF (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
  add_definitions(-D_WIN32_WINNT=0x0501)


ENDIF()

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(Boost COMPONENTS system thread filesystem date_time log log_setup REQUIRED)


SET(_FILES_m3d src/lms_mini_lib.cpp src/3dUnitDriver.cpp src/encoder_driver.cpp )
SET(_HEADERS_m3d hpp/lms_mini_lib.hpp src/3dUnitDriver.hpp src/encoder_driver.hpp )

#set export for headers




if(Boost_FOUND)
    link_directories(${Boost_LIBRARY_DIRS})
    include_directories(${Boost_INCLUDE_DIRS} hpp ${PROJECT_BINARY_DIR}) 
  
    MESSAGE("Boost information")  
    MESSAGE("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")  
    MESSAGE("Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")  
    MESSAGE("Boost Libraries: ${Boost_LIBRARIES}") 
 
   
else()
	message( FATAL_ERROR "You really need BOOST library. Find if BOOST_ROOT and BOOST_LIBRARYDIR is set to correct BOOST dir. CMake will exit." )
endif()
#library, shared for m3d unit
	add_library(m3d_driver_lib SHARED ${_FILES_m3d})
	GENERATE_EXPORT_HEADER(m3d_driver_lib)

	add_executable(3d_unit_basicTest src/driver.cpp)
	target_link_libraries(3d_unit_basicTest ${Boost_LIBRARIES} ${Boost_LIBRARIES} m3d_driver_lib)
