cmake_minimum_required(VERSION 2.8)
project(ch5)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(filter filter.cpp)
target_link_libraries(filter ${OpenCV_LIBS})

add_executable(demo_filter demo_filter.cpp)
target_link_libraries(demo_filter ${OpenCV_LIBS})

add_executable(moph moph.cpp)
target_link_libraries(moph ${OpenCV_LIBS})

add_executable(resize resize.cpp)
target_link_libraries(resize ${OpenCV_LIBS})

add_executable(thres thres.cpp)
target_link_libraries(thres ${OpenCV_LIBS})
