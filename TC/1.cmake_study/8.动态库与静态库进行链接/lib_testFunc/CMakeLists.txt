aux_source_directory (. SRC_LIST)

add_library (testFunc_shared SHARED ${SRC_LIST})
add_library (testFunc_static STATIC ${SRC_LIST})

set_target_properties (testFunc_shared PROPERTIES OUTPUT_NAME "testFunc")
set_target_properties (testFunc_static PROPERTIES OUTPUT_NAME "testFunc")

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 第一行，使用aux_source_directory把当前目录下的源文件存列表存放到变量SRC_LIST里
# 第二、三行，add_library: 生成动态库或静态库
# 第1个参数指定库的名字
# 第2个参数决定是动态还是静态，如果没有就默认静态
# 第3个参数指定生成库的源文件
# 第四、五行，set_target_properties: 设置输出的名称，还有其它功能，如设置库的版本号等等
# - 可以看出前面使用set_target_properties重新定义了库的输出名字，
# - 如果不用set_target_properties也可以，那么库的名字就是add_library里定义的名字，
# - 只是我们连续2次使用add_library指定库名字时，这个名字不能相同，
# - 而set_target_properties可以把名字设置为相同，只是最终生成的库文件后缀不同，这样相对来说会好看点

# 第六行，LIBRARY_OUTPUT_PATH: 库文件的默认输出路径，这里设置为工程目录下的lib目录
