cmake_minimum_required(VERSION 3.17)
project(plotTrajectory)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/eigen3")
include_directories(${Pangolin_INCLUDE_DIRS})

# 添加pangolin包
find_package(Pangolin REQUIRED)

add_executable(plotTrajectory main.cpp)
target_link_libraries(plotTrajectory ${Pangolin_LIBRARIES})