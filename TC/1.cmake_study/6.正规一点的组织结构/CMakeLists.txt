cmake_minimum_required (VERSION 2.8)

project (demo)

aux_source_directory (src SRC_LIST)

include_directories (include)

add_executable (main ${SRC_LIST})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 第一行，意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
# 第二行，表示本工程信息，也就是工程名叫demo
# 第三行，用于将 src 目录下的所有源文件的名字保存在变量 SRC_LIST 中
# 第四行，用于设定目录，这些设定的目录将被编译器用来查找 include 文件
# 第五行，表示最终要生成的elf文件的名字叫main，使用的源文件是 src目录下的所有源文件
# 第六行，命令set，是用于定义变量的。
# EXECUTABLE_OUT_PATH、PROJECT_SOURCE_DIR是CMake自带的预定义变量
# EXECUTABLE_OUTPUT_PATH ：目标二进制可执行文件的存放位置
# PROJECT_SOURCE_DIR：工程的根目录
# 所以，这里set的意思是把存放elf文件的位置设置为工程根目录下的bin目录
