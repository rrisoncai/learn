cmake_minimum_required( VERSION 2.8 )
project(stereo)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( stereo disparity.cpp )
target_link_libraries( stereo ${Pangolin_LIBRARIES} ${OpenCV_LIBS})
