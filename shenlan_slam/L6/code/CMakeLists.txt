cmake_minimum_required(VERSION 2.8)
project(l6)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

add_executable(optical_flow optical_flow.cpp)
target_link_libraries(optical_flow ${OpenCV_LIBS})

add_executable(direct_method direct_method.cpp)
target_link_libraries(direct_method ${OpenCV_LIBS} ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES})

add_executable(disparity disparity.cpp)
target_link_libraries(disparity ${OpenCV_LIBS} ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES})
