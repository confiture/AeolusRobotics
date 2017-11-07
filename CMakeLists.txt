cmake_minimum_required(VERSION 2.8)

#set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

project( view )
find_package( OpenCV REQUIRED )

set(SOURCE_FILES
  src/ImageProcessing.cpp
  src/ImageUtility.cpp
  )

add_executable( view  src/view.cpp ${SOURCE_FILES})
add_executable( command_line  src/CommandLine.cpp ${SOURCE_FILES})

target_link_libraries( view ${OpenCV_LIBS} )
target_link_libraries( command_line ${OpenCV_LIBS} )
