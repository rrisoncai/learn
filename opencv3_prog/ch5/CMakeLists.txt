cmake_minimum_required(VERSION 2.8)
project(ch5)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(write_xml write_xml.cpp)
target_link_libraries(write_xml ${OpenCV_LIBS})

add_executable(read_xml read_xml.cpp)
target_link_libraries(read_xml ${OpenCV_LIBS})
