cmake_minimum_required(VERSION 2.8)
project(direct_ba)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -march=native")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Pangolin REQUIRED)
find_package(Sophus REQUIRED)
find_package(OpenCV REQUIRED)
find_package(G2O REQUIRED)
find_package(Cholmod)

include_directories("/usr/include/eigen3")
include_directories(${Pangolin_INCLUDE_DIRS})
include_directories(${G2O_INCLUDE_DIRS})
include_directories(${CHOLMOD_INCLUDE_DIR})

set( THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${Sophus_LIBRARIES}
        ${CHOLMOD_LIBRARIES}
        ${Pangolin_LIBRARIES}
      g2o_core g2o_stuff g2o_types_slam3d g2o_types_sba g2o_solver_csparse g2o_csparse_extension )
add_executable(directba directBA.cpp)
target_link_libraries(directba ${THIRD_PARTY_LIBS})
