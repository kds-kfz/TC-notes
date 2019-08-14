aux_source_directory(${PROJECT_SOURCE_DIR}/common SRC_COMMON)

aux_source_directory(. SRC_SRC)

set(SRC_LIST ${SRC_SRC} ${SRC_COMMON})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR/common})

link_directories(${PROJECT_SOURCE_DIR}/lib)

link_libraries(gflags glog pthread dl z)

add_executable(Daemon ${SRC_LIST})

#第一行，用于将 工程绝对目录下的common目录下的源文件保存到 SRC_COMMON
#第二行，将当前目录下的源文件保存到 SRC_SRC
#第三行，显示定义变量，SRC_LIST 代替后面两个值
#第四行，显示定义变量，EXECUTABLE_OUTPUT_PATH 代替后面两个值
#第五行，主要是指定要链接的库文件的路径
#第六行，链接gflags glog pthread libdl.so z 动态库
#第七行，用于指定从 SRC_LIST 源文件，编译出可执行文件 Daemon
