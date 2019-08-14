# 编 辑 者：yinling
# 第1次修改时间：2019年06月24日
# 第1次修改版本说明：V1.0 该 Makefile 用于管理 CMakeLists.txt 以及目录构造文件拷贝
# 第2次修改时间：2019年07月03日
# 第2次修改版本说明：V1.1 版本，添加配置服务
# 第3次修改时间：2019年07月04日
# 第3次修改版本说明：V1.2 版本，完善single build clean. 更好兼容各项服务编译

.PHONY: default clean clean-all build single force

ifeq ($(JOBS),)
  JOBS := $(shell grep -c ^processor /proc/cpuinfo 2 > /dev/null)
  ifeq ($(JOBS),)
	JOBS := 1
  endif
endif

BUILD_DIR := build
AllServer := HKocr Comperssion

# 注意目标一栏依赖关系，层层递进

$(Server): build
	### 构建[$(Server)]项目 ###
	@[ -d $(BUILD_DIR) ] && \
		cd $(BUILD_DIR); cmake -j$(JOBS) .. && make && \
		echo [$(Server)]项目构建已完成
	@mkdir bin/$(Server); mkdir bin/$(Server)/bin; cp bin/Daemon bin/$(Server)Daemon

	# 新项目需要手动修改 CMakeLists.txt 内容
	# 在修改对应的配置文件与依赖关系，配置文件会在程序或者依赖库中使用
	@cp $(Server)/bin/* bin/$(Server)/bin/ && \
	rm -f bin/$(Server)/bin/libopencv* && \
	cp -r $(Server)/confing bin/$(Server)/bin/ && \
	cp $(Server)/conf/* bin/$(Server)/bin/config/ && \
	cp -r tmp bin/$(Server)/bin/ && \
	cp -r template bin/$(Server)/bin/ && \
	cp $(Server)/bat/* bin/$(Server)/bin/ && \
	cp -r $(Server)/lib bin/$(Server)/ && \
	rm bin/$(Server)/lib/createln* bin/$(Server)/bin/cp.sh
ifeq ($(Server), HKocr)
	cp -r lib/* bin/$(Server)/lib/
endif
ifeq ($(Server), Comperssion)
	mv $(Server)/lib/ctget $(Server)/bin
endif
	### 构建[$(Server)]依赖初步完成  ###
	@cd bin/$(Server)/bin; sh del.sh; chmod 755 *; mkdir log

	@cd bin; tar -cvf $(Server)-`date +%Y-%m-%d`.tar.gz $(Server)/

	# 次目录下的依赖库需要收到那个执行程序后，将需要的依赖添加到该目录下
	@cp common_lib/* bin/$(Server)/lib

	### 构建[$(Server)]依赖全部完成 ###
	echo #########+    build $(Server) Node server Success    +#########

build: force
ifeq ($(strip $(Server)), $(filter $(Server), $(AllServer)))
#ifeq ($(filter $(Server), $(AllServer)),)
	### 构建[$(Server)]服务目录 ###
	cd $(Server)/batl sh cp.sh; sh createln.sh
	@[ -d $(BUILD_DIR) ] || \
		mkdir $(BUILD_DIR)
else
	# [$(Server)] 此服务尚未实现
endif

default: force

force:
ifndef Server
	@echo -e "you have to define Server the this values: \n \
	HKocr \n \
	Comperssion \n \
	command: \n \
	Server=HKocr maek or Server=Comperssion make single"
	@exit 1
endif

single: force
	# 不管什么服务，之前都定义好了，需要修改好源文件，这里只需要再次进入 build make 即可
	make -C build
	cp $(Server)/bin/$(Server) bin/$(Server)/bin/ -f
	### 编译single[$(Server)]服务已完成 ###

clean:
	make -C build clean
	rm *.log -f
	rm HKocr/bin/HKocr* -f
	rm Comperssion/bin/Comperssion* -f

clean-all:
	rm *.log -f
	rm bin/* -rf
	rm build -rf
	rm HKocr/bin/HKocr* -f
	rm Comperssion/bin/Comperssion* -f

