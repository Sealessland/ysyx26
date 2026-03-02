#!/bin/bash
# "一生一芯"项目开发容器启动脚本（最终版）
# 使用方法: ./start-dev-final.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"

WORK_DIR=$(pwd)

echo "========================================="
echo "一生一芯项目开发容器启动脚本"
echo "========================================="
echo "工作目录: ${WORK_DIR}"
echo "镜像: ${IMAGE_NAME}"
echo "========================================="

# 检查podman是否安装
if ! command -v podman &> /dev/null; then
    echo "错误: 未找到podman，请先安装podman"
    echo "安装命令: sudo apt install podman"
    exit 1
fi

# 检查镜像是否存在
if ! podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
    echo "错误: 镜像 ${IMAGE_NAME} 不存在"
    echo "请先运行以下命令构建镜像："
    echo "  podman commit ${CONTAINER_NAME} ${IMAGE_NAME}"
    echo ""
    echo "或者使用基础镜像："
    echo "  IMAGE_NAME=localhost/ysyx-ubuntu-env:latest"
    exit 1
fi

# 检查容器是否已存在
if podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo "✓ 容器 '${CONTAINER_NAME}' 已存在"

    # 检查容器是否正在运行
    if podman ps --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
        echo "✓ 容器正在运行"
    else
        echo "→ 启动容器..."
        podman start ${CONTAINER_NAME}
        echo "✓ 容器已启动"
    fi

    echo "→ 进入容器..."
    exec podman exec -it ${CONTAINER_NAME} /bin/bash
else
    echo "→ 创建新容器..."
    podman run --name ${CONTAINER_NAME} \
        -h ysyx-container \
        -v ${WORK_DIR}:/home/sealessland/ysyx-workbench:Z \
        -w /home/sealessland/ysyx-workbench \
        --privileged \
        -it ${IMAGE_NAME} /bin/bash
fi
