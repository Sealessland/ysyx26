#!/bin/bash
# "一生一芯"项目开发容器启动脚本
# 使用方法: ./start-dev.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_REPO="mma0mvtf.f7ncot.xuanyuan.run/ubuntu"
IMAGE_TAG="22.04"
FULL_IMAGE="${IMAGE_REPO}:${IMAGE_TAG}"

WORK_DIR=$(pwd)
USER_NAME="sealessland"
USER_UID=$(id -u)

echo "========================================="
echo "一生一芯项目开发容器启动脚本"
echo "========================================="
echo "工作目录: ${WORK_DIR}"
echo "用户名: ${USER_NAME}"
echo "用户UID: ${USER_UID}"
echo "镜像: ${FULL_IMAGE}"
echo "========================================="

# 检查 podman 是否安装
if ! command -v podman &> /dev/null; then
    echo "错误: 未找到 podman，请先安装 podman"
    echo "安装命令: sudo apt install podman"
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

    # 创建容器
    podman run --name ${CONTAINER_NAME} \
        -h ysyx-container \
        -v ${WORK_DIR}:/home/${USER_NAME}/ysyx-workbench:Z \
        -w /home/${USER_NAME}/ysyx-workbench \
        -e USER=${USER_NAME} \
        -e USER_UID=${USER_UID} \
        --privileged \
        -it ${FULL_IMAGE} /bin/bash

    # 注意: 首次启动后需要手动创建用户，请参考 docker-tutorial.md
    echo ""
    echo "========================================="
    echo "首次启动提示"
    echo "========================================="
    echo "容器已创建并启动！"
    echo ""
    echo "首次使用需要执行以下操作："
    echo "1. 更新并安装 sudo: apt update && apt install -y sudo"
    echo "2. 创建用户:"
    echo "   useradd -m -s /bin/bash -u ${USER_UID} ${USER_NAME}"
    echo "   usermod -aG sudo ${USER_NAME}"
    echo "   echo '${USER_NAME} ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers.d/${USER_NAME}"
    echo "   chmod 440 /etc/sudoers.d/${USER_NAME}"
    echo "3. 设置密码: passwd ${USER_NAME}"
    echo "4. 切换用户: su - ${USER_NAME}"
    echo "5. 安装编译工具: 参考教程安装必要的软件包"
    echo ""
    echo "详细教程请查看: docker-tutorial.md"
    echo "========================================="
fi
