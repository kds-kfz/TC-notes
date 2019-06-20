aux_source_directory (. SRC_LIST)

include_directories (../lib_testFunc)

link_directories (${PROJECT_SOURCE_DIR}/lib)

add_executable (main ${SRC_LIST})

# 默认是使用动态库
target_link_libraries (main testFunc)

# 指定使用静态库链接
#target_link_libraries (main libtestFunc.a)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# 当执行cmake时，就会进入src目录去找src目录下的 CMakeLists.txt
# 第一行，使用aux_source_directory把当前目录下的源文件存列表存放到变量SRC_LIST里
# 第二行，用于设定目录，这些设定的目录将被编译器用来查找 include 文件
# 第三行，link_directories: 添加非标准的共享库搜索路径
# 第四行，表示最终要生成的elf文件的名字叫main，使用的源文件是 src目录下的所有源文件
# 第五行，target_link_libraries: 把目标文件与库文件进行链接
# 默认是使用动态库，如果lib目录下只有静态库，那么这种写法就会去链接静态库
# 指定使用动态库还是静态库
# target_link_libraries (main libtestFunc.so)或target_link_libraries (main libtestFunc.a)
# 第六行，命令set，是用于定义变量的。
# EXECUTABLE_OUT_PATH、PROJECT_SOURCE_DIR是CMake自带的预定义变量
# EXECUTABLE_OUTPUT_PATH ：目标二进制可执行文件的存放位置
# PROJECT_SOURCE_DIR：工程的根目录
# 所以，这里set的意思是把存放elf文件的位置设置为工程根目录下的bin目录
