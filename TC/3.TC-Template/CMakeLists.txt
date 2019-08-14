cmake_minimum_required (VERSION 2.8)

project (demo)

add_definitions("-g")

message(STATUS, "This is BINARY dir", ${PROJECT_BINARY_DIR})
message(STATUS, "This is SOURCE dir", ${PROJECT_SOURCE_DIR})

if (win32)
    message(STATUS "This is windows.")
elseif(unix)
    message(STATUS "This is unix.")
elseif(apple)
    message(STATUS "This is apple.")
else
    message(STATUS "This is apple.")
endif(win32)

add_subdirectory(daemon)

add_subdirectory(HKocr)

#第一行，意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
#第二行，是表示本工程信息，也就是工程名叫demo
#第三行，添加编译参数
# 默认编译生成的可执行文件是无法使用 gdb 来跟踪或调试的，因为可执行程序中没有可供 gdb 调试使用的特殊信息，
# 为了将必要的调试信息整合到可执行文件中，我们便需要用到 -g 选项，这样生成的可执行程序，倘若出现问题，
# 便可以使用 gdb 找出问题具体出现的位置，便于问题的解决
#第四、五行，输出信息
#最后两行，用于添加一个需要进行构建的子目录
