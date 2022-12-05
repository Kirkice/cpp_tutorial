# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.19)

# 项目信息
project(reflect)

#Cpp 版本
set(CMAKE_CXX_STANDARD 20)

#设置头文件路径
set(INC_DIR ../3rd_party/rttr/src)

##设置链接库路径
#set(LINK_DIR ../external/fbxsdk/lib)

#引入头文件
include_directories(${INC_DIR})

##引入库文件
#link_directories(${LINK_DIR})

# 指定生成目标
add_executable(reflect meta_macro.h static_reflect.h static_reflect.cpp rttr_test.cpp)

##将第三方库连接在一起
#target_link_libraries(smooth-normal-tools libfbxsdk)