project(mysql-client)

# 库文件输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# 源码
file(GLOB_RECURSE SRCS *.cpp)
# 编译为库文件
add_library(${PROJECT_NAME} STATIC ${SRCS})