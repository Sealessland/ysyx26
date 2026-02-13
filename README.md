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

- **[PERSISTENT_WORKING.md](PERSISTENT_WORKING.md)** - 🔑 持久化工作指南（推荐）
- **[QUICKSTART.md](QUICKSTART.md)** - 🚀 快速上手指南
- **[HOST_CONTAINER_GUIDE.md](HOST_CONTAINER_GUIDE.md)** - 📖 宿主机与容器切换完整教程
- **[ENVIRONMENT_INFO.md](ENVIRONMENT_INFO.md)** - 📊 系统环境信息报告

### 常用命令

```bash
./enter.sh            # 进入容器（推荐）
exit                  # 退出容器
./save.sh             # 保存容器修改
podman ps -a          # 查看容器状态
podman stop ysyx-dev  # 停止容器
```

### 容器特性

- ✅ 文件自动同步（宿主机 ↔ 容器）
- ✅ sudo 免密码（sealessland 用户）
- ✅ 预装所有编译工具
- ✅ NEMU 已编译可运行
- ✅ 配置清华镜像源

### sudo 使用

```bash
./enter.sh
sudo apt update     # 更新软件包
sudo apt install xxx # 安装软件
sudo whoami         # 验证权限
```

详细信息请查看 [PERSISTENT_WORKING.md](PERSISTENT_WORKING.md)

---

[lecture note]: https://ysyx.oscc.cc/docs/
