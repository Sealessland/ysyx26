# "一生一芯"工程项目

这是"一生一芯"的工程项目. 通过运行
```bash
bash init.sh subproject-name
```
进行初始化, 具体请参考[实验讲义][lecture note].

## 🐳 Docker 容器开发环境

### 快速开始

```bash
# 一键进入容器（推荐）
./enter.sh

# 在容器中编译运行 NEMU
cd nemu
make CONFIG_ISA=riscv32 CONFIG_ENGINE=interpreter
make run

# 退出容器（修改已自动保存）
exit

# 保存容器修改为镜像（可选）
./save.sh
```

### 核心文件

- **[docs/README.md](docs/README.md)** - 📚 文档中心（推荐从这里开始）
- **[QUICKSTART.md](QUICKSTART.md)** - 🚀 3步快速开始
- **[docs/HOW_TO_SAVE.md](docs/HOW_TO_SAVE.md)** - 💾 保存修改完整指南

### 常用命令

```bash
# 标准工作流（推荐）
./enter.sh            # 进入容器
cd nemu && make run   # 编译运行
exit                 # 退出（自动保存代码）
./save.sh            # 保存配置

# 神奇操作（重要节点）
./save-and-enter.sh   # 保存后进入
./enter-smart.sh     # 智能提示版
```

### 容器特性

- ✅ 文件自动同步（宿主机 ↔ 容器）
- ✅ sudo 免密码（sealessland 用户）
- ✅ 预装所有编译工具
- ✅ NEMU 已编译可运行
- ✅ 配置清华镜像源
- ✅ 智能保存提示（新）

### 更多脚本

```bash
./enter-smart.sh     # 智能提示版（超过1小时提示保存）
./save-and-enter.sh   # 保存后进入（重要节点）
./container-setup.sh # 容器环境优化
```

详细文档请查看 **[docs/README.md](docs/README.md)**

---

[lecture note]: https://ysyx.oscc.cc/docs/
