cmake_minimum_required (VERSION 2.8)

project (demo)

add_executable(main main.c testFunc.c)

#第一行意思是表示cmake的最低版本要求是2.8，我们安装的是 cmake version 3.1.0
#第二行是表示本工程信息，也就是工程名叫demo
#第三行比较关键，表示最终要生成的elf文件的名字叫main，使用的源文件是main.c testFunc.c
