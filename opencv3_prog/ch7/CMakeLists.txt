cmake_minimum_required(VERSION 2.8)
project(ch5)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(canny canny.cpp)
target_link_libraries(canny ${OpenCV_LIBS})

add_executable(hough hough.cpp)
target_link_libraries(hough ${OpenCV_LIBS})
