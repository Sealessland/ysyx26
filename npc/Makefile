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

verify: $(VERIFY_TEST) $(BUILD_DIR)/filelist.f
	mkdir -p $(VERIFY_DIR)
	@# Patch generated DPI-C stub ports to match Chisel io_ naming without touching sources.
	cd $(BUILD_DIR) && \
		test -f DPIC_Fetch.sv && perl -pi -e 's/\braddr\b/io_raddr/g; s/\brdata\b/io_rdata/g' DPIC_Fetch.sv && \
		test -f DPIC_LSU.sv && perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g; s/\bcmd\b/io_cmd/g; s/\baddr\b/io_addr/g; s/\bwdata\b/io_wdata/g; s/\blen\b/io_len/g; s/\brdata\b/io_rdata/g' DPIC_LSU.sv && \
		test -f DPIC_Ebreak.sv && perl -pi -e 's/\bclk\b/io_clk/g; s/\ben\b/io_en/g' DPIC_Ebreak.sv && \
		$(VERILATOR) $(VERILATOR_FLAGS) -Mdir verilator -o sim -f filelist.f ../$(VERIFY_TEST)
	./$(VERIFY_DIR)/sim

.PHONY: verilog help bsp idea clean verify
