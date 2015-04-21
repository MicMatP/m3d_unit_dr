cmake_minimum_required(VERSION 2.8.8)
#SET(CMAKE_BUILD_TYPE Debug)

PROJECT(M3dUnit)

SET(PROJECT_NAME M3dUnit)

 
set(MANDALA_3DUNIT_MAJOR_VERSION 0)
set(MANDALA_3DUNIT_MINOR_VERSION 1)
set(MANDALA_3DUNIT_PATCH_VERSION 0)
set(MANDALA_3DUNIT_VERSION  ${MANDALA_3DUNIT_MAJOR_VERSION}.${MANDALA_3DUNIT_MINOR_VERSION}.${MANDALA_3DUNIT_PATCH_VERSION})

IF (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
  add_definitions(-D_WIN32_WINNT=0x0501)
  add_definitions(-DWIN32_LEAN_AND_MEAN)

ENDIF()

# add sources of library
SET(_FILES_m3d src/lms_mini_lib.cpp src/3dUnitDriver.cpp src/encoder_driver.cpp src/3dUnitTypeSerialization.cpp )
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


add_subdirectory(tools/ManualCalibration)
add_subdirectory(tools/rawMeasurmentToTxt)
add_subdirectory(examples)

set_target_properties(m3d_driver_lib PROPERTIES 
	DEBUG_POSTFIX d
	PUBLIC_HEADER  ${_HEADERS_m3d}
	)
install (TARGETS m3d_driver_lib
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin
		 PUBLIC_HEADER DESTINATION include
		 INCLUDES DESTINATION include)
		 
install (DIRECTORY hpp/ DESTINATION include)
set(m3dunit_INCLUDE_DIRS "include")

include(CMakePackageConfigHelpers)


write_basic_package_version_file(m3dunitVersion.cmake VERSION 0.0.1 COMPATIBILITY AnyNewerVersion)


configure_package_config_file (m3dunitConfig.cmake.in ${CMAKE_BINARY_DIR}/m3dunitConfig.cmake
								INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
								PATH_VARS m3dunit_INCLUDE_DIRS)
export ( TARGETS m3d_driver_lib FILE "${CMAKE_BINARY_DIR}/m3dunitTargets.cmake" )
export ( PACKAGE m3dunit ) 
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/m3dunitConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/m3dunitVersion.cmake
        DESTINATION  "cmake")
		
#install(FILES "${PROJECT_BINARY_DIR}/m3dunit-config.cmake" DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/m3dunitTargets.cmake" DESTINATION "cmake")
#CPACK (windows)
IF (WIN32)

SET(_BOOST_DLL_TO_COPY ${BOOST_LIBRARY_DIR}/ src/3dUnitDriver.hpp src/encoder_driver.hpp )

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME "Mandala Universal Driver")
set(CPACK_PACKAGE_VENDOR "mandalarobotics.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Mandala Universal Driver")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Mandala Universal Driver")
SET(CPACK_NSIS_MODIFY_PATH ON)

INCLUDE(CPack)

endif()