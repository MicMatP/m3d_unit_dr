cmake_minimum_required(VERSION 2.8.3)

#project(ManualM3DCalibration)
SET(CMAKE_BUILD_TYPE Debug)

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

set (M3D_BUILD_TOOL_MANUAL_CALIBRATION TRUE CACHE BOOL "Build tool ManualCalibration")
if (M3D_BUILD_TOOL_MANUAL_CALIBRATION)
	# Find includes in corresponding build directories
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	set(CMAKE_AUTOMOC ON)
	# Find the QtWidgets library
	find_package(Qt5Widgets)
	find_package(Qt5OpenGL)
#	find_package(PCL 1.7 REQUIRED)

#	include_directories(${PCL_INCLUDE_DIRS})
#	link_directories(${PCL_LIBRARY_DIRS})
#	add_definitions(${PCL_DEFINITIONS})

	set(UI_FILES
	    mainwindow.ui
            scanwindow.ui
	)


	qt5_wrap_ui(UI_HEADERS ${UI_FILES})

	include_directories(${Qt5Widgets_INCLUDE_DIRS})

	# Use the compile definitions defined in the Qt 5 Widgets module
	add_definitions(${Qt5Widgets_DEFINITIONS})

	# Add compiler flags for building executables (-fPIE)Fpcl
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


	# Tell CMake to create the helloworld executable
        add_executable(pclCalibrationManual main.cpp  mainwindow.cpp scanwindow.cpp  myglwidget.cpp ${UI_FILES})
	qt5_use_modules(pclCalibrationManual Widgets OpenGL)
	#Link the helloworld executable to the Qt 5 widgets library.
        target_link_libraries(pclCalibrationManual m3d_driver_lib ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${GLUT_LIBRARY} Qt5::Widgets )

endif()
