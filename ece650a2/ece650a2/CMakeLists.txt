cmake_minimum_required(VERSION 2.8)
project(a3-ece650)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)
add_library(graph graph.hpp graph.cpp)
add_library(rgen rgen.h rgen.cpp)

add_executable(a2-ece650 a2-ece650.cpp)
add_executable(a3-ece650 a3-ece650.cpp)

target_link_libraries(a2-ece650 PRIVATE graph)
target_link_libraries(a3-ece650 PRIVATE rgen)

install(PROGRAMS a1ece650.py DESTINATION bin)
install(TARGETS a2-ece650 a3-ece650 RUNTIME DESTINATION bin)
