cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp puzzle_struct.h puzzle_struct.cpp puzzle_funcs.h puzzle_funcs.cpp)
