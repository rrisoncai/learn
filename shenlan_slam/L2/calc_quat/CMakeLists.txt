cmake_minimum_required(VERSION 2.8)
project(calc_quat)

include_directories("/usr/include/eigen3")
add_executable(calc_quat calc_quat.cpp)
