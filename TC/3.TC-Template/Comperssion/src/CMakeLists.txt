aux_source_directory(${PROJECT_SOURCE_DIR}/common SRC_COMMON)
aux_source_directory(. SRC_SRC)

set(SRC_LIST ${SRC_SRC} ${SRC_COMMON})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Comperssion/bin)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/Comperssion/include ${PROJECT_SOURCE_DIR}/common)

link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/Comperssion/lib)


link_libraries(glog pthread dl z uuid TC_SICS_IMGPORCESS.6.1.2)

add_executable(Comperssion ${SRC_LIST})

#第一行，将工程所在的全路径 common 目录下的源文件保存在 SRC_COMMON
#第二行，将当前目录下的源文件保存在 SRC_SRC
#第三行，设置变量 SRC_LIST，代替 SRC_SRC 和 SRC_COMMON
#第四行，用于设定目录，这些设定的目录将被编译器用来查找 include 文件
#第五行，添加非标准的共享库搜索路径
#第六行，链接glog pthread dl z uuid等动态库
#第七行，用于指定从 SRC_LIST 源文件，编译出可执行文件 Comperssion
