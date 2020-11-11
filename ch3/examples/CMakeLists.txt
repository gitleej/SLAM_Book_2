cmake_minimum_required(VERSION 3.17)
project(examples)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件
include_directories("/usr/include/eigen3")

add_executable(examples main.cpp)