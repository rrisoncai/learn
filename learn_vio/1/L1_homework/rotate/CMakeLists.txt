cmake_minimum_required(VERSION 2.8)
project(rotate)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 添加Eigen头文件
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(rotate rotate.cpp)
