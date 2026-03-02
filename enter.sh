#!/bin/bash
# 持久进入 Ubuntu 容器 - 完整版
# 使用方法: ./enter.sh

set -e

CONTAINER_NAME="ysyx-dev"
IMAGE_NAME="ysyx-dev-ready:latest"
FALLBACK_IMAGE="localhost/ysyx-ubuntu-env:latest"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 颜色输出
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${BLUE}ℹ${NC} $1"
}

log_success() {
    echo -e "${GREEN}✓${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

echo "========================================="
echo "一生一芯开发环境"
echo "========================================="
log_info "工作目录: ${SCRIPT_DIR}"
echo "========================================="
echo ""

# 检查 podman
if ! command -v podman &> /dev/null; then
    echo "❌ 错误: 未找到 podman"
    echo "   安装命令: sudo apt install podman"
    exit 1
fi

# 选择镜像
if podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${IMAGE_NAME}$"; then
    USE_IMAGE="${IMAGE_NAME}"
    log_success "使用镜像: ${IMAGE_NAME}"
elif podman images --format '{{.Repository}}:{{.Tag}}' | grep -q "^${FALLBACK_IMAGE}$"; then
    USE_IMAGE="${FALLBACK_IMAGE}"
    log_warning "使用默认镜像: ${FALLBACK_IMAGE}"
else
    echo "❌ 错误: 未找到可用镜像"
    exit 1
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
fi

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
echo '用户: '$(whoami)' (UID: '$(id -u)')'
echo '工作目录: '$(pwd)
"
echo "========================================="
echo ""
echo "提示:"
echo "  - 编辑代码会自动同步到宿主机"
echo "  - 容器内的修改（如 ~/.bashrc）需要保存镜像"
echo "  - 输入 'exit' 退出容器（容器保持运行）"
echo "  - 运行 ./save.sh 保存容器修改为镜像"
echo ""
echo "快速命令:"
echo "  cd nemu && make CONFIG_ISA=riscv32      # 编译"
echo "  cd nemu && make run                     # 运行"
echo "  source ~/.bashrc                       # 重载配置"
echo ""
echo "========================================="
echo ""

# 进入容器
exec podman exec -it ${CONTAINER_NAME} /bin/bash
