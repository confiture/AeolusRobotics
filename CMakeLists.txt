cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

project( view )
find_package( OpenCV REQUIRED )

add_executable( view  src/view.cpp src/ImageProcessing.cpp)
add_executable( command_line  src/CommandLine.cpp src/ImageProcessing.cpp)

target_link_libraries( view ${OpenCV_LIBS} )
target_link_libraries( command_line ${OpenCV_LIBS} )
