.PHONY: default clean clean-all

ifeq ($(JOBS),)
  JOBS := $(shell grep -c ^processor /proc/cpuinfo 2>/dev/null)
  ifeq ($(JOBS),)
    JOBS := 1
  endif
endif

TARGETS = main

BUILD_DIR = ./build
DEST_DIR = ./bin
LOG_DIR = ./log
LOG_OBJ = $(TARGETS)_cmake.log

default: $(TARGETS)

main: build bin log
	### 自动生成目录与可执行文件
	@[ -d $(BUILD_DIR) ] && \
		cd $(BUILD_DIR); cmake -j$(JOBS) .. > $(LOG_OBJ) && \
		echo "目标文件${TARGETS}编译已完成" || \
		echo "找不到$(BUILD_DIR)目录，编译停止"

build:
	@[ -d $(BUILD_DIR) ] && \
		echo "build 目录已存在" || \
		mkdir $(BUILD_DIR)
bin:
	@[ -d $(DEST_DIR) ] && \
		echo "bin 目录已存在" || \
		mkdir $(DEST_DIR)
log:
	@[ -d $(LOG_DIR) ] && \
		echo "log 目录已存在" || \
		mkdir $(LOG_DIR)

clean:
	rm $(BUILD_DIR)/* $(DEST_DIR)/* $(LOG_DIR)/*.log -rf

clean-all:
	rm $(BUILD_DIR) $(DEST_DIR) $(LOG_DIR) .*.swp -rf
