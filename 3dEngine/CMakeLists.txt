cmake_minimum_required(VERSION 3.22)
project(3dEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3dEngine main.cpp headers/graphing_structs.h src/graphing_structs.cpp headers/graphing_algorithms.h src/graphing_algorithms.cpp)
