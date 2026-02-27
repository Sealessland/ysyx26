BUILD_DIR = ./build
VERIFY_DIR = $(BUILD_DIR)/verilator
VERIFY_TEST = tests/verify_fetch_decode.cpp
VERILATOR ?= verilator
VERILATOR_FLAGS = --cc --exe --build -j 8 -Wall -Wno-fatal -Wno-UNUSEDSIGNAL --trace --trace-structs --trace-depth 20 --top-module CoreTop -CFLAGS "-std=c++17"

PRJ = playground

# 包含公共的 git_commit 函数
-include ../Makefile

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i -j 8 $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)
help:
	mill -i $(PRJ).runMain Elaborate --help

bsp:
	mill -i mill.bsp.BSP/install

idea:
	mill -i mill.idea.GenIdea/idea

clean:
	-rm -rf $(BUILD_DIR)

BIN ?= build/build/rtthread-riscv32e-npc.bin

build-sim: $(VERIFY_TEST) $(BUILD_DIR)/filelist.f
	mkdir -p $(VERIFY_DIR)
	@# Patch generated DPI-C stub ports to match Chisel io_ naming without touching sources.
	cd $(BUILD_DIR) && \
		test -f DPIC_Fetch.sv && perl -pi -e 's/\braddr\b/io_raddr/g; s/\brdata\b/io_rdata/g' DPIC_Fetch.sv && \
		test -f DPIC_LSU.sv && perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g; s/\bcmd\b/io_cmd/g; s/\baddr\b/io_addr/g; s/\bwdata\b/io_wdata/g; s/\blen\b/io_len/g; s/\brdata\b/io_rdata/g' DPIC_LSU.sv && \
		test -f DPIC_Ebreak.sv && perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g' DPIC_Ebreak.sv && \
		$(VERILATOR) $(VERILATOR_FLAGS) -Mdir verilator -o sim -f filelist.f ../$(VERIFY_TEST)

verify: build-sim
	./$(VERIFY_DIR)/sim --bin build/build/rtthread-riscv32e-npc.bin --max-cycles 20000000  --require-ebreak

run: build-sim
	./$(VERIFY_DIR)/sim --bin $(BIN) --max-cycles 20000000 --no-trace --require-ebreak

semu-verilog: $(BUILD_DIR)/filelist.f
	@echo "--- 为 sEMU 生成独立的 Verilator 模型 ---"
	mkdir -p sEMU/dut/verilator
	@# 复制 DPI-C 文件到 sEMU/dut 并修改端口名
	cp $(BUILD_DIR)/DPIC_*.sv sEMU/dut/
	cd sEMU/dut && \
		perl -pi -e 's/\braddr\b/io_raddr/g; s/\brdata\b/io_rdata/g' DPIC_Fetch.sv && \
		perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g; s/\bcmd\b/io_cmd/g; s/\baddr\b/io_addr/g; s/\bwdata\b/io_wdata/g; s/\blen\b/io_len/g; s/\brdata\b/io_rdata/g' DPIC_LSU.sv && \
		perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g' DPIC_Ebreak.sv
	@# 生成 filelist，修正路径为相对于 sEMU/dut 的路径
	grep -v "DPIC_" $(BUILD_DIR)/filelist.f | sed 's|^|../../build/|' > sEMU/dut/filelist_semu.f
	echo "DPIC_Fetch.sv" >> sEMU/dut/filelist_semu.f
	echo "DPIC_LSU.sv" >> sEMU/dut/filelist_semu.f
	echo "DPIC_Ebreak.sv" >> sEMU/dut/filelist_semu.f
	cd sEMU/dut && $(VERILATOR) --cc --trace --trace-structs --trace-depth 20 \
		--top-module CoreTop -Wall -Wno-fatal -Wno-UNUSEDSIGNAL \
		-Mdir verilator -f filelist_semu.f
	@echo "--- sEMU Verilator 模型已生成到 sEMU/dut/verilator/ ---"

# 新设计的专业 sEMU 模拟器工作流目标
build-semu: semu-verilog
	@echo "--- 配置并构建专业模拟器 sEMU ---"
	mkdir -p sEMU/build
	@# 每次都重新调用 cmake，使得 sEMU/CMakeLists.txt 内部的 file(GLOB) 能够抓取到最新的被拆分的 .cpp 文件
	cd sEMU/build && cmake .. -DCMAKE_BUILD_TYPE=Release && $(MAKE) -j8
	@echo "--- sEMU 构建完成 ---"

run-semu: build-semu
	@echo "--- 启动 sEMU ---"
	./sEMU/build/sEMU

# Ensure filelist.f exists by running verilog if needed
$(BUILD_DIR)/filelist.f:
	$(MAKE) verilog

.PHONY: verilog help bsp idea clean verify semu-verilog build-semu run-semu
