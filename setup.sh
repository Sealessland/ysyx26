#!/bin/bash
# 初始化"一生一芯"开发环境
# 使用方法: ./setup.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"
FALLBACK_IMAGE="localhost/ysyx-ubuntu-env:latest"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "========================================="
echo "一生一芯开发环境初始化"
echo "========================================="
echo "工作目录: ${SCRIPT_DIR}"
echo "========================================="

# 检查 podman
if ! command -v podman &> /dev/null; then
    echo "❌ 错误: 未找到 podman"
    echo "   安装命令: sudo apt install podman"
    exit 1
fi

# 检查容器是否已存在
if podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo "⚠️  容器 '${CONTAINER_NAME}' 已存在"
    read -p "是否删除并重新创建? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        podman rm -f ${CONTAINER_NAME}
        echo "✓ 已删除旧容器"
    else
        echo "→ 使用现有容器"
        exit 0
    fi
fi

# 选择镜像
if podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
    USE_IMAGE="${IMAGE_NAME}"
    echo "✓ 找到配置好的镜像: ${IMAGE_NAME}"
elif podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${FALLBACK_IMAGE}$"; then
    USE_IMAGE="${FALLBACK_IMAGE}"
    echo "✓ 找到默认镜像: ${FALLBACK_IMAGE}"
else
    echo "❌ 错误: 未找到可用镜像"
    echo "   请确保 ${IMAGE_NAME} 或 ${FALLBACK_IMAGE} 存在"
    exit 1
fi

# 创建容器
echo "→ 创建容器..."
podman run --name ${CONTAINER_NAME} \
    -h ysyx-container \
    -v ${SCRIPT_DIR}:/home/sealessland/ysyx-workbench:Z \
    -w /home/sealessland/ysyx-workbench \
    -e USER=sealessland \
    -e USER_UID=1000 \
    --userns keep-id \
    --privileged \
    -d ${USE_IMAGE} sleep infinity > /dev/null

echo "✓ 容器已创建"
echo ""
echo "========================================="
echo "初始化完成！"
echo "========================================="
echo ""
echo "下一步操作:"
echo "  1. 进入容器: ./dev.sh"
echo "  2. 编译 NEMU: cd nemu && make CONFIG_ISA=riscv32 CONFIG_ENGINE=interpreter"
echo "  3. 运行 NEMU: make run"
echo ""
echo "更多信息请查看: HOST_CONTAINER_GUIDE.md"
echo "========================================="
