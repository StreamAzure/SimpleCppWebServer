cmake_minimum_required(VERSION 3.22)

project(server)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/..) # 把可执行文件的生成位置改到SimpleCppServer目录下

include_directories(${PROJECT_SOURCE_DIR}/../include/)

# 查找当前目录下的所有源文件,并将名称保存到 DIR_LIB_SRCS 变量 
aux_source_directory(. DIR_LIB_SRCS)
 
# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_LIB_SRCS})
