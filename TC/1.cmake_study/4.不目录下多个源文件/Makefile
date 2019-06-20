.PHONY: default clean

ifeq ($(JOBS),)
  JOBS := $(shell grep -c ^processor /proc/cpuinfo 2>/dev/null)
  ifeq ($(JOBS),)
    JOBS := 1
  endif
endif


BUILD_DIR = ./build
#DEST_DIR = ./bin

TARGETS = main
default: $(TARGETS)

main: build
	### 自动生成目录与可执行文件
	@[ -d $(BUILD_DIR) ] && \
		cd $(BUILD_DIR); cmake -j$(JOBS) ..

build:
	@[ -d $(BUILD_DIR) ] && \
		echo "build 目录已存在" || \
		mkdir $(BUILD_DIR) && \
		echo "build 目录已生成"
clean:
	rm $(BUILD_DIR) -rf
