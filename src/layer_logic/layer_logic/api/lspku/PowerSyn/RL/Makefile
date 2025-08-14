# 主 Makefile
BUILD_DIR ?= build

all: configure install

configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

install:
	@cmake --build $(BUILD_DIR) --target install_all

clean:
	@rm -rf $(BUILD_DIR)
	@cd sources/PowerAwareSynthesis/netlist/abc && $(MAKE) clean
	@conda env remove -n rlgym --yes

.PHONY: all configure install clean