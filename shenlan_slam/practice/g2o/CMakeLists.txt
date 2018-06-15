cmake_minimum_required(VERSION 3.9)
project(g2o)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(G2O REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Cholmod)

add_executable(g2o main.cpp)
