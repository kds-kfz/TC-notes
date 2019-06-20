cmake_minimum_required (VERSION 2.8)

project (demo)

aux_source_directory(. SRC_LIST)

add_executable(main ${SRC_LIST})

#第一行 ,意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
#第二行，是表示本工程信息，也就是工程名叫demo
#第三行，使用aux_source_directory把当前目录下的源文件存列表存放到变量SRC_LIST里
#第四行，在add_executable里调用SRC_LIST（注意调用变量时的写法）
