cmake_minimum_required(VERSION 2.8)
project(ceres_ba)

find_package(Ceres REQUIRED)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

include_directories("/usr/include/eigen3/")
include_directories(${Ceres_INCLUDE_DIRS})

add_executable(ceres_ba ceres_ba.cpp)
target_link_libraries(ceres_ba ceres glog)
