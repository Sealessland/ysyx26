#!/bin/bash
# 一键进入"一生一芯"开发容器
# 使用方法: ./dev.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "========================================="
echo "一生一芯开发容器"
echo "========================================="
echo "工作目录: ${SCRIPT_DIR}"
echo "容器名称: ${CONTAINER_NAME}"
echo "========================================="

# 检查 podman
if ! command -v podman &> /dev/null; then
    echo "❌ 错误: 未找到 podman"
    echo "   安装命令: sudo apt install podman"
    exit 1
fi

# 检查镜像是否存在
if ! podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
    echo "⚠️  镜像 ${IMAGE_NAME} 不存在"
    echo "   将使用默认镜像: localhost/ysyx-ubuntu-env:latest"
    IMAGE_NAME="localhost/ysyx-ubuntu-env:latest"

    if ! podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
        echo "❌ 错误: 默认镜像也不存在"
        echo "   请先运行以下命令拉取或构建镜像"
        exit 1
    fi
fi

# 检查容器是否存在
if podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo "✓ 容器 '${CONTAINER_NAME}' 已存在"

    # 检查容器是否正在运行
    if podman ps --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
        echo "✓ 容器正在运行"
    else
        echo "→ 启动容器..."
        podman start ${CONTAINER_NAME} > /dev/null
        echo "✓ 容器已启动"
    fi
else
    echo "→ 创建新容器..."
    podman run --name ${CONTAINER_NAME} \
        -h ysyx-container \
        -v ${SCRIPT_DIR}:/home/sealessland/ysyx-workbench:Z \
        -w /home/sealessland/ysyx-workbench \
        -e USER=sealessland \
        -e USER_UID=1000 \
        --userns keep-id \
        --privileged \
        -d ${IMAGE_NAME} sleep infinity > /dev/null

    echo "✓ 容器已创建并启动"
fi

echo ""
echo "→ 进入容器..."
echo "  提示: 输入 'exit' 或按 Ctrl+D 退出容器"
echo "  提示: 宿主机当前目录已挂载到 /home/sealessland/ysyx-workbench"
echo "  提示: 当前用户: sealessland (UID=1000)"
echo ""

# 进入容器
exec podman exec -it ${CONTAINER_NAME} /bin/bash
