cmake_minimum_required(VERSION 3.22)
project(3dEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(3dEngine main.cpp src/graph_algorithms.cpp headers/graph_algorithms.h src/grapher.cpp headers/grapher.h)
