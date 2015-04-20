cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

add_executable(rawMeasurmentToTxt rawMeasurmentToTxt.cpp)
target_link_libraries(rawMeasurmentToTxt m3d_driver_lib ${Boost_LIBRARIES})
set_target_properties(rawMeasurmentToTxt PROPERTIES DEBUG_POSTFIX d)
install (TARGETS rawMeasurmentToTxt
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)
