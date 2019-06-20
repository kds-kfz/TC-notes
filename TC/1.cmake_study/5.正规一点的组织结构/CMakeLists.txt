cmake_minimum_required (VERSION 2.8)

project (demo)

add_subdirectory (src)

#第一行 ,意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
#第二行，是表示本工程信息，也就是工程名叫demo
#第三行，命令可以向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制的存放位置
