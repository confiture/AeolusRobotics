cmake_minimum_required(VERSION 2.8)
project( view )
find_package( OpenCV REQUIRED )

add_executable( view  src/view.cpp src/ImageProcessing.cpp)

target_link_libraries( view ${OpenCV_LIBS} )
