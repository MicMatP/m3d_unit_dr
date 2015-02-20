cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(PCL 1.5 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(pcl_manual calibration.cpp)
target_link_libraries(pcl_manual m3d_driver_lib ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})