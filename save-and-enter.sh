#!/bin/bash
# 组合命令：保存容器后进入
# 使用方法: ./save-and-enter.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo "========================================="
echo "保存并进入容器"
echo "========================================="
echo ""

# 检查容器是否运行
if podman ps --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo -e "${BLUE}→ 容器正在运行，准备保存...${NC}"

    # 保存容器
    TIMESTAMP=$(date +%Y%m%d-%H%M%S)
    BACKUP_IMAGE="ysyx-dev-backup:${TIMESTAMP}"

    echo "保存为: ${BACKUP_IMAGE}"
    podman commit ${CONTAINER_NAME} ${BACKUP_IMAGE} > /dev/null
    echo -e "${GREEN}✓ 保存成功${NC}"

    # 更新默认镜像
    podman tag ${BACKUP_IMAGE} ${IMAGE_NAME} > /dev/null
    echo -e "${GREEN}✓ 已更新默认镜像${NC}"

elif podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo -e "${BLUE}→ 容器未运行，直接启动...${NC}"
else
    echo -e "${BLUE}→ 容器不存在，创建新容器...${NC}"
fi

echo ""
echo "========================================="
echo "进入容器"
echo "========================================="

# 调用 enter.sh
exec "${SCRIPT_DIR}/enter.sh"
