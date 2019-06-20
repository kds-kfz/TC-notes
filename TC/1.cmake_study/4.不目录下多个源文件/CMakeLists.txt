cmake_minimum_required (VERSION 2.8)

project (demo)

include_directories (test_func test_func1)

aux_source_directory(test_func SRC_LIST)
aux_source_directory(test_func1 SRC_LIST1)


add_executable(main main.c ${SRC_LIST} ${SRC_LIST1})

#第一行 ,意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
#第二行，是表示本工程信息，也就是工程名叫demo
#第三行，该命令是用来向工程添加多个指定头文件的搜索路径，路径之间用空格分隔
#第四、五行，使用aux_source_directory把当前目录下的源文件存列表存放到变量SRC_LIST、SRC_LIST1里
#第六行，在add_executable里调用SRC_LIST（注意调用变量时的写法）
