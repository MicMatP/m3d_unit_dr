#########################################################
# Simple example
#########################################################
add_executable(simpleWriter simpleWriter.cpp)
target_link_libraries(simpleWriter ${Boost_LIBRARIES} ${Boost_LIBRARIES} m3d_driver_lib)
set_target_properties(simpleWriter PROPERTIES DEBUG_POSTFIX d)
set (M3D_BUILD_EXAMPLE_GLUT TRUE CACHE BOOL "Build GLUT Example")
 install (TARGETS simpleWriter
 ARCHIVE DESTINATION lib
 LIBRARY DESTINATION lib
 RUNTIME DESTINATION bin)
#########################################################
# Simple example OpenGL
#########################################################

if(M3D_BUILD_EXAMPLE_GLUT AND OPENGL_FOUND AND GLUT_FOUND)
	add_executable(simpleGL simpleGL.cpp)
	target_link_libraries(simpleGL  m3d_driver_lib ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${GLUT_LIBRARY} )
	set_target_properties(simpleGL PROPERTIES DEBUG_POSTFIX d)
		
	 install (TARGETS simpleGL
	 ARCHIVE DESTINATION lib
	 LIBRARY DESTINATION lib
	 RUNTIME DESTINATION bin)
endif()

