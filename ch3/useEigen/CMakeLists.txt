cmake_minimum_required(VERSION 3.17)
project(useEigen)

set(CMAKE_CXX_STANDARD 14)

# 添加頭文件
include_directories("/usr/include/eigen3")

add_executable(useEigen eigenMatrix.cpp)