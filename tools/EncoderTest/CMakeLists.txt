cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

add_executable(encoderTest encoderTest.cpp)
target_link_libraries(encoderTest m3d_driver_lib)