[cmake]有没清理所有编译生成文件的clean命令
故在统计目录建立Makefile，用于编译以及清除
备注：
该写法使用了1个CMakeLists.txt，这种写法是生成一个elf文件，链接动态或静态库
生成后可以在bin目录下执行，查看elf文件使用了哪些库
readelf -d main
