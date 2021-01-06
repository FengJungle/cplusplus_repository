cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)


# 查找目录下的所有源文件
# 并将名称保存到 CPP_LIST1 变量
aux_source_directory(. CPP_LIST1)
# 将目录mathlib下的所有源文件保存到CPP_LIST2
aux_source_directory(./funclib CPP_LIST2)

# 添加 common 子目录
add_subdirectory(common)

# 指定生成目标
add_executable(main ${CPP_LIST1} ${CPP_LIST2})

# 添加链接库
target_link_libraries(main common)