# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.19)

# 项目信息
project(analyse_shader)

#Cpp 版本
set(CMAKE_CXX_STANDARD 20)

#设置头文件路径
set(INC_DIR F:/Program Files/boost_1_80_0/)

#引入头文件
include_directories(${INC_DIR})

# 指定生成目标
add_executable(analyse_shader analyse_shader.h analyse_shader.cpp shader_struct.h load_shader.cpp load_shader.h property.cpp property.h main.cpp)
