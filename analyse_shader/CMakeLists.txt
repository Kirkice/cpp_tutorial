# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.19)

# 项目信息
project(analyse_shader)

#Cpp 版本
set(CMAKE_CXX_STANDARD 20)

#设置头文件路径
set(INC_DIR ../3rd_party/boost_1_80_0/include/)

#引入头文件
include_directories(${INC_DIR})

#设置链接库路径
set(LINK_DIR ../3rd_party/boost_1_80_0/lib/)

#引入库文件
link_directories(${LINK_DIR})

# 指定生成目标
add_executable(analyse_shader property.h property.cpp shader_struct.h load_shader.h load_shader.cpp Shader.h Shader.cpp analyse_shader.h analyse_shader.cpp main.cpp generate_hlsl_code.cpp generate_hlsl_code.h pipeline_state_object.cpp pipeline_state_object.h)

target_link_libraries(analyse_shader libboost_thread-vc142-mt-x64-1_80 libboost_system-vc142-mt-x64-1_80)