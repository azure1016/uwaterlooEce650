cmake_minimum_required(VERSION 2.8)
project(a2ece650)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)
add_library(graph graph.hpp graph.cpp)

add_executable(a2-ece650 a2-ece650.cpp)

target_link_libraries(a2-ece650 PRIVATE graph)
