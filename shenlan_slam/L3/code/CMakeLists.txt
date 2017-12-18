cmake_minimum_required( VERSION 2.8 )
project( draw_trajectory)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 为使用 sophus，您需要使用find_package命令找到它
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )

find_package( Pangolin REQUIRED)
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( draw_trajectory draw_trajectory.cpp )
target_link_libraries( draw_trajectory ${Sophus_LIBRARIES} ${Pangolin_LIBRARIES})
