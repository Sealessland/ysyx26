# 文档中心

这里是"一生一芯"项目的所有文档。

## 📚 文档索引

### 🚀 快速开始

| 文档 | 说明 | 优先级 |
|------|------|--------|
| [../README.md](../README.md) | 项目主 README | ⭐⭐⭐⭐⭐ |
| [../QUICKSTART.md](../QUICKSTART.md) | 3步快速开始 | ⭐⭐⭐⭐⭐⭐ |

### 🔑 脚本使用

| 脚本 | 说明 | 推荐度 |
|------|------|--------|
| [../enter.sh](../enter.sh) | 一键进入容器 | ⭐⭐⭐⭐⭐⭐ |
| [../enter-smart.sh](../enter-smart.sh) | 智能提示版 | ⭐⭐⭐⭐ |
| [../save.sh](../save.sh) | 保存容器修改 | ⭐⭐⭐⭐⭐ |
| [../save-and-enter.sh](../save-and-enter.sh) | 保存后进入 | ⭐⭐⭐⭐⭐ |
| [../setup.sh](../setup.sh) | 环境初始化 | ⭐⭐⭐ |
| [../container-setup.sh](../container-setup.sh) | 容器优化 | ⭐⭐⭐ |

### 📖 详细教程

| 文档 | 说明 | 长度 |
|------|------|------|
| **HOW_TO_SAVE.md** | 保存修改完整指南 | 中 |
| **PERSISTENT_WORKING.md** | 持久化工作指南 | 长 |
| **PERSISTENT_SETUP_COMPLETE.md** | 持久化配置报告 | 中 |
| **ENVIRONMENT_INFO.md** | 系统环境信息 | 长 |
| **SUDO_CONFIG_COMPLETE.md** | sudo 配置报告 | 短 |
| **TUTORIAL_COMPLETE.md** | 教程完成报告 | 长 |

### 📚 参考资料

| 文档 | 说明 |
|------|------|
| [../docker-tutorial.md](../docker-tutorial.md) | Docker/Podman 完整教程 |
| [../podman-cheatsheet.md](../podman-cheatsheet.md) | Podman 命令速查表 |
| [../DOCKER_README.md](../DOCKER_README.md) | Docker 快速入门 |
| [../HOST_CONTAINER_GUIDE.md](../HOST_CONTAINER_GUIDE.md) | 宿主机与容器切换 |
| [../SETUP_COMPLETE.md](../SETUP_COMPLETE.md) | 环境设置报告 |
| [../Dockerfile](../Dockerfile) | 自定义镜像构建 |

---

## 🎯 按场景查找文档

### 我是新手，从零开始

1. 阅读 [../README.md](../README.md)
2. 阅读 [../QUICKSTART.md](../QUICKSTART.md)
3. 运行 `./enter.sh` 开始使用

### 我想知道如何保存修改

1. 阅读 [HOW_TO_SAVE.md](HOW_TO_SAVE.md)（推荐）
2. 或阅读 [../PERSISTENT_WORKING.md](PERSISTENT_WORKING.md)（详细）

### 我想了解系统环境

1. 阅读 [ENVIRONMENT_INFO.md](ENVIRONMENT_INFO.md)
2. 运行 `./enter.sh` 查看容器信息

### 我需要脚本参考

- 查看 [../QUICKSTART.md](../QUICKSTART.md) 的快速命令
- 查看 [../podman-cheatsheet.md](../podman-cheatsheet.md) 的 Podman 命令

### 我想深入理解 Docker/Podman

1. 阅读 [../docker-tutorial.md](../docker-tutorial.md)
2. 参考 [../HOST_CONTAINER_GUIDE.md](../HOST_CONTAINER_GUIDE.md)

---

## 🔍 快速问题解答

### Q: 如何进入容器？

**A**: 运行 `./enter.sh` 或 `./enter-smart.sh`

### Q: 修改会自动保存吗？

**A**: 工作目录的修改自动保存，容器内其他修改需要运行 `./save.sh`

详见 [HOW_TO_SAVE.md](HOW_TO_SAVE.md)

### Q: 如何使用 sudo？

**A**: 容器内 `sudo 免密码`，详见 [SUDO_CONFIG_COMPLETE.md](SUDO_CONFIG_COMPLETE.md)

### Q: NEMU 如何编译运行？

**A**: `cd nemu && make CONFIG_ISA=riscv32 && make run`

### Q: 有哪些"神奇操作"？

**A**:
- `./enter-smart.sh` - 智能提示保存
- `./save-and-enter.sh` - 保存后进入

---

## 📝 文档维护

### 文档结构

```
docs/
├── README.md                     # 本文件（文档索引）
├── HOW_TO_SAVE.md               # 保存修改指南
├── PERSISTENT_WORKING.md         # 持久化工作指南
├── PERSISTENT_SETUP_COMPLETE.md   # 配置完成报告
├── ENVIRONMENT_INFO.md           # 系统环境信息
├── SUDO_CONFIG_COMPLETE.md      # sudo 配置报告
└── TUTORIAL_COMPLETE.md         # 教程完成报告
```

### 更新说明

- 主要文档移动到 `docs/` 目录
- 脚本保留在根目录方便使用
- README 作为文档索引

---

**祝你开发顺利！** 🚀
