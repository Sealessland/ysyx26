#!/bin/bash
# 智能进入容器 - 带保存提示
# 使用方法: ./enter-smart.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"
FALLBACK_IMAGE="localhost/ysyx-ubuntu-env:latest"
TIMESTAMP_FILE=".last_save_time"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

log_info() { echo -e "${BLUE}ℹ${NC} $1"; }
log_success() { echo -e "${GREEN}✓${NC} $1"; }
log_warning() { echo -e "${YELLOW}⚠${NC} $1"; }

cd "$SCRIPT_DIR"

# 检查是否需要提示保存
check_save_prompt() {
    if [ -f "$TIMESTAMP_FILE" ]; then
        last_save=$(cat "$TIMESTAMP_FILE" 2>/dev/null || echo "0")
        current_time=$(date +%s)
        elapsed=$((current_time - last_save))

        # 超过1小时提示
        if [ $elapsed -gt 3600 ]; then
            echo ""
            log_warning "距离上次保存已超过 $(($elapsed / 3600)) 小时"
            echo ""
            read -p "是否先保存当前容器状态？ (y/N): " -n 1 -r
            echo
            if [[ $REPLY =~ ^[Yy]$ ]]; then
                log_info "正在保存容器..."
                ./save.sh
                echo ""
            fi
        fi
    fi
}

echo "========================================="
echo "一生一芯开发环境（智能版）"
echo "========================================="
log_info "工作目录: ${SCRIPT_DIR}"
echo "========================================="
echo ""

# 检查 podman
if ! command -v podman &> /dev/null; then
    echo "❌ 错误: 未找到 podman"
    exit 1
fi

# 选择镜像
USE_IMAGE="$IMAGE_NAME"
if ! podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
    USE_IMAGE="$FALLBACK_IMAGE"
    if ! podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${FALLBACK_IMAGE}$"; then
        echo "❌ 错误: 未找到可用镜像"
        exit 1
    fi
fi

# 检查容器是否存在
if ! podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    log_info "容器不存在，创建新容器..."

    podman run --name ${CONTAINER_NAME} \
        -h ysyx-container \
        -v ${SCRIPT_DIR}:/home/sealessland/ysyx-workbench:Z \
        -w /home/sealessland/ysyx-workbench \
        -e USER=sealessland \
        -e USER_UID=1000 \
        --userns keep-id \
        --privileged \
        -d ${USE_IMAGE} sleep infinity

    log_success "容器已创建"
    # 记录时间戳
    date +%s > "$TIMESTAMP_FILE"
fi

# 提示保存
check_save_prompt

# 检查容器状态
if podman ps --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    log_success "容器正在运行"
else
    log_info "启动容器..."
    podman start ${CONTAINER_NAME} > /dev/null
    log_success "容器已启动"
fi

echo ""
echo "========================================="
echo "容器信息"
echo "========================================="
podman exec ${CONTAINER_NAME} bash -c "
echo '用户: '$(whoami)' (UID: '$(id -u)')
echo '工作目录: '$(pwd)
"
echo "========================================="
echo ""
echo "提示:"
echo "  - 工作目录修改自动同步到宿主机"
echo "  - 重要配置修改后运行 ./save.sh"
echo "  - 或使用 ./save-and-enter.sh (保存后进入)"
echo ""

# 进入容器
exec podman exec -it ${CONTAINER_NAME} /bin/bash
