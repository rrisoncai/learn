cmake_minimum_required(VERSION 2.8)

project(bal)
set(CMAKE_BUILD_TYPE "Debug")
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

Find_Package(Eigen3 REQUIRED)

include_directories("/usr/include/eigen3")

add_executable(bal bal.cpp)

target_link_libraries(bal ceres glog)
