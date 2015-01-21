cmake_minimum_required(VERSION 2.8)

PROJECT(MANDALA_3dUnit)
#iF YOU DOES NOT HAVE LIBRARIES IN PATH, YOU CAN EASILY DEFINE ALL HERE
#SET(BOOST_ROOT H:/Libs/boost_1_57_0vs2012x64)
#SET(BOOST_LIBRARYDIR H:/Libs/boost_1_57_0vs2012x64/lib64-msvc-10.0)


SET(PROJECT_NAME MANDALA_3dUnit)

IF (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
  add_definitions(-D_WIN32_WINNT=0x0501)
ENDIF()


SET(_FILES_m3d src/lms_mini_lib.cpp src/3dUnitDriver.cpp src/encoder_driver.cpp )
SET(_HEADERS_m3d hpp/lms_mini_lib.hpp src/3dUnitDriver.hpp src/encoder_driver.hpp )


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIR})
	add_definitions(${GLUT_DEFINITIONS})
else()
    message(ERROR " GLUT not found!")
endif()
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories(${OpenGL_INCLUDE_DIR})
	link_directories(${OpenGL_LIBRARY_DIR})
	add_definitions(${OpenGL_DEFINITIONS})
else()
    message(ERROR " OPENGL not found!")
endif()
#########################################################
# FIND BOOST
#########################################################
find_package(Boost COMPONENTS system thread filesystem date_time REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${Boost_INCLUDE_DIRS} hpp ${PROJECT_BINARY_DIR}  ${GLUT_INCLUDE_DIRS}) 
MESSAGE("Boost information")  
MESSAGE("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")  
MESSAGE("Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")  
MESSAGE("Boost Libraries: ${Boost_LIBRARIES}") 
 
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)



#########################################################
# M3d LIB
#########################################################
add_library(m3d_driver_lib SHARED ${_FILES_m3d})
#GENERATE_EXPORT_HEADER(m3d_driver_lib)

#########################################################
# Simple example
#########################################################
add_executable(simpleWrtier examples/simpleWrtier.cpp)
target_link_libraries(simpleWrtier ${Boost_LIBRARIES} ${Boost_LIBRARIES} m3d_driver_lib)
#########################################################
# Simple example OpenGL
#########################################################
set (M3D_BUILD_EXAMPLE_GLUT TRUE CACHE BOOL "Build GLUT Example")

if(M3D_BUILD_EXAMPLE_GLUT AND OPENGL_FOUND AND GLUT_FOUND)
	add_executable(simpleGL examples/simpleGL.cpp)
	target_link_libraries(simpleGL  m3d_driver_lib ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${GLUT_LIBRARY} )

endif()

file(COPY ${CMAKE_SOURCE_DIR}/sampleConfig/3dUnitCfg.xml  DESTINATION ${CMAKE_BINARY_DIR})



add_subdirectory(tools/ManualCalibration)

