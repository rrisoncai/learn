cmake_minimum_required(VERSION 2.8)
PROJECT(sayhello)

set(CMAKE_BUILD_TYPE "Release")
include_directories("include")

add_library(hello SHARED src/hello.cpp)
add_executable(sayhello src/useHello.cpp)
target_link_libraries(sayhello hello)

# install libhello.so to /usr/local/lib/
INSTALL(TARGETS hello LIBRARY DESTINATION lib)

# install hello.h to /usr/local/include/
INSTALL(FILES include/hello.h DESTINATION include)
