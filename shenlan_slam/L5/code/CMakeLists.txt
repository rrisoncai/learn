cmake_minimum_required(VERSION 2.8)
project(computeORB)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("/usr/include/eigen3")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(computeORB computeORB.cpp)
target_link_libraries(computeORB ${OpenCV_LIBS})

add_executable(E2Rt E2Rt.cpp)
target_link_libraries(E2Rt ${Sophus_LIBRARIES})

add_executable(GN-BA GN-BA.cpp)
target_link_libraries(GN-BA ${Sophus_LIBRARIES})

add_executable(align_trajectory align_trajectory.cpp)
target_link_libraries(align_trajectory ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES})
