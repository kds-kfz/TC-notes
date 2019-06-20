.PHONY: default clean clean-all build lib log

ifeq ($(JOBS),)
  JOBS := $(shell grep -c ^processor /proc/cpuinfo 2>/dev/null)
  ifeq ($(JOBS),)
    JOBS := 1
  endif
endif

TARGETS = main

BUILD_DIR = ./build
DEST_DIR = ./bin
LIB_DIR = ./lib
LOG_DIR = ./log
LOG_OBJ = $(TARGETS)_cmake.log

default: $(TARGETS)

main: build bin lib log
	### 自动生成目录与可执行文件
	@[ -d $(BUILD_DIR) ] && \
		cd $(BUILD_DIR); cmake -j$(JOBS) .. > $(LOG_OBJ) && \
		echo "目标文件${TARGETS}编译已完成" || \
		echo "找不到$(BUILD_DIR)目录，编译停止"

build:
	@[ -d $(BUILD_DIR) ] || \
		mkdir $(BUILD_DIR)
bin:
	@[ -d $(DEST_DIR) ] || \
		mkdir $(DEST_DIR)
lib:
	@[ -d $(LIB_DIR) ] || \
		mkdir $(LIB_DIR)
log:
	@[ -d $(LOG_DIR) ] || \
		mkdir $(LOG_DIR)

clean:
	rm $(BUILD_DIR)/* $(LIB_DIR)/* $(DEST_DIR)/* $(LOG_DIR)/*.log -rf

clean-all:
	rm $(BUILD_DIR) $(LIB_DIR) $(DEST_DIR) $(LOG_DIR) .*.swp -rf
