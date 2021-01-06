cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

# 语法： SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]]) 
# 指令功能: 用来显式的定义变量 
# 例子: SET (SRC_LST main.c other.c) 
# 说明: 用变量代替值，例子中定义SRC_LST代替后面的字符串。

# 设置环境变量 CMAKE_INCLUDE_CURRENT_DIR
# 自动添加 CMAKE_CURRENT_SOURCE_DIR 到当前处理的 CMakeLists.txt
set(CMAKE_INCLUDE_CURRENT_DIR ON)

 # DEBUG 为编译开关，中间的字符串为描述信息，ON/OFF 为默认选项
option(DEBUG "a macro debug to print more info" OFF)

# configure_file(<input> <output>
# [COPYONLY] [ESCAPE_QUOTES] [@ONLY] [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
# 功能： 将 <input> 文件里面的内容全部复制到 <output> 文件中
# PROJECT_SOURCE_DIR : 路径指向当前正在处理的源目录（CMakeLists.txt所在目录）
configure_file(
    "${PROJECT_SOURCE_DIR}/configure.h.in" 
    "${PROJECT_SOURCE_DIR}/configure.h"
    )

# 查找目录下的所有源文件
# 并将名称保存到 CPP_LIST1 变量
aux_source_directory(. CPP_LIST1)
# 将目录mathlib下的所有源文件保存到CPP_LIST2
aux_source_directory(./funclib CPP_LIST2)

# 添加 common 子目录
add_subdirectory(common)

# 指定生成目标
add_executable (main ${CPP_LIST1} ${CPP_LIST2})
target_link_libraries (main  common)

# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")