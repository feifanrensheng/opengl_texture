cmake_minimum_required( VERSION 2.8 )
project( test )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )
set( OpenCV_DIR "/usr/local/opencv-2.4.9/share/OpenCV")

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


# find_package( OpenCV REQUIRED ) # use this if in OpenCV2 


include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${OpenGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIRS})

add_definitions(${GLUT_DEFINITIONS})
add_definitions(${OpenGL_DEFINITIONS})

link_directories(${OpenGL_LIBRARY_DIR})
link_directories(${OpenCV_LIBRARY_DIR})



add_executable(8 8.cpp )
target_link_libraries( 8 ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
