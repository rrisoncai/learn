cmake_minimum_required(VERSION 2.8)
project(ceres_test)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

add_executable(ceres_test test_ceres.cpp)
target_link_libraries(ceres_test ${CERES_LIBRARIES} ${OpenCV_LIBS})

add_executable(hello hello.cpp)
target_link_libraries(hello ${CERES_LIBRARIES} ${OpenCV_LIBS})

add_executable(powell powell.cpp)
target_link_libraries(powell ${CERES_LIBRARIES} ${OpenCV_LIBS})

add_executable(curve_fitting curve_fitting.cpp)
target_link_libraries(curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS})

add_executable(ba ba.cpp)
target_link_libraries(ba ${CERES_LIBRARIES})
