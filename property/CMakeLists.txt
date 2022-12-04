# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.19)

# 项目信息
project(property)

#Cpp 版本
set(CMAKE_CXX_STANDARD 20)

# 指定生成目标
add_executable(property property.h property.cpp)