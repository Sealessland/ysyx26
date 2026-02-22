# 默认构建目录
BUILD_DIR ?= build
# 构建类型 (Debug, Release等)
BUILD_TYPE ?= Release
# CMake附加参数
CMAKE_ARGS ?=
# 执行文件的运行参数
RUN_ARGS ?=
# C++附加编译参数
CXX_FLAGS ?=

# 声明伪目标
.PHONY: all build run clean docs serve-docs clean-docs

# 默认目标
all: build

# 配置并编译
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_CXX_FLAGS="$(CXX_FLAGS)" \
		$(CMAKE_ARGS) ..
	@$(MAKE) -C $(BUILD_DIR)
	@cp -f $(BUILD_DIR)/compile_commands.json . 2>/dev/null || true

# 运行程序
run: build
	@echo "--- 正在运行 sEMU [$(BUILD_TYPE)] ---"
	@./$(BUILD_DIR)/sEMU $(RUN_ARGS)

# 定制文档和第三方依赖目录
DOC_DIR ?= html
DOXY_CSS_REPO ?= doxygen-awesome-css

# 清理构建输出
clean:
	@echo "--- 清理生成的文件 ---"
	@rm -rf $(BUILD_DIR) docs/build

# ---------------------------------------------------------
# 文档生成器管线 (Doxygen + Awesome-CSS 渲染)
# ---------------------------------------------------------
docs:
	@echo "--- 正在准备 Doxygen 文档生成环境 ---"
	@if [ ! -d "$(DOXY_CSS_REPO)" ]; then \
		echo "--- 未找到 doxygen-awesome-css 主题，正在克隆 ---"; \
		git clone https://github.com/jothepro/doxygen-awesome-css.git $(DOXY_CSS_REPO) --depth=1; \
	fi
	@if [ ! -f "Doxyfile" ]; then \
		echo "--- 初始化 Doxyfile 默认配置并追加高级选项 ---"; \
		doxygen -g Doxyfile; \
		sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "sEMU"/g' Doxyfile; \
		sed -i 's/OUTPUT_LANGUAGE        = English/OUTPUT_LANGUAGE        = Chinese/g' Doxyfile; \
		echo 'GENERATE_HTML = YES' >> Doxyfile; \
		echo 'HTML_EXTRA_STYLESHEET = doxygen-awesome-css/doxygen-awesome.css' >> Doxyfile; \
		echo 'GENERATE_LATEX = NO' >> Doxyfile; \
		echo 'INPUT = include src' >> Doxyfile; \
		echo 'RECURSIVE = YES' >> Doxyfile; \
		echo 'HAVE_DOT = YES' >> Doxyfile; \
		echo 'UML_LOOK = YES' >> Doxyfile; \
		echo 'CALL_GRAPH = YES' >> Doxyfile; \
		echo 'CALLER_GRAPH = YES' >> Doxyfile; \
		echo 'EXTRACT_ALL = YES' >> Doxyfile; \
		echo 'EXTRACT_PRIVATE = YES' >> Doxyfile; \
	fi
	@echo "--- 开始调用 Doxygen 生成代码全景图与 API 结构 ---"
	@doxygen Doxyfile
	@echo "--- 恭喜！文档已成功生成到 $(DOC_DIR)/ 目录。 ---"

# 开启本地 HTTP 服务预览文档
serve-docs: docs
	@echo "--- 启动文档预览服务 ---"
	@echo "--- 请在 Web 浏览器中访问: http://localhost:8000 ---"
	@echo "--- (提示: 若想停止服务请在终端按下 Ctrl+C ) ---"
	@python3 -m http.server 8000 --directory $(DOC_DIR)

# 深度清理：销毁生成的文档、配置文件与主题源码
clean-docs:
	@echo "--- 清理所有的离线文档与渲染组件 ---"
	@rm -rf $(DOC_DIR) latex Doxyfile $(DOXY_CSS_REPO)
