aux_source_directory (. SRC_LIST)

include_directories (../include)

add_executable(main ${SRC_LIST})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 当执行cmake时，就会进入src目录去找src目录下的 CMakeLists.txt
# 第一行，使用aux_source_directory把当前目录下的源文件存列表存放到变量SRC_LIST里
# 第二行，用于设定目录，这些设定的目录将被编译器用来查找 include 文件
# 第三行，表示最终要生成的elf文件的名字叫main，使用的源文件是 src目录下的所有源文件
# 第四行，命令set，是用于定义变量的。
# EXECUTABLE_OUT_PATH、PROJECT_SOURCE_DIR是CMake自带的预定义变量
# EXECUTABLE_OUTPUT_PATH ：目标二进制可执行文件的存放位置
# PROJECT_SOURCE_DIR：工程的根目录
# 所以，这里set的意思是把存放elf文件的位置设置为工程根目录下的bin目录
