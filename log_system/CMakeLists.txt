# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.19)

# 项目信息
project(log_system)

#Cpp 版本
set(CMAKE_CXX_STANDARD 20)

#设置头文件路径
set(spd_log_include ../3rd_party/Spdlog/include/)
set(boost_include ../3rd_party/boost_1_80_0/include/)

#引入头文件
include_directories(
        ${spd_log_include}
        ${boost_include}
        )

#设置链接库路径
set(boost_link ../3rd_party/boost_1_80_0/lib/)

#引入库文件
link_directories(${boost_link})

# 指定生成目标
add_executable(log_system main.cpp log.cpp log.h)

target_link_libraries(log_system libboost_thread-vc142-mt-x64-1_80 libboost_system-vc142-mt-x64-1_80)