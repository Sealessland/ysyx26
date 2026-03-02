#!/bin/bash
# 保存容器修改为镜像 - 持久化脚本
# 使用方法: ./save.sh [镜像名称]

set -e

CONTAINER_NAME="ysyx-dev"
DEFAULT_IMAGE="ysyx-dev-ready:latest"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

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
echo "保存容器修改"
echo "========================================="
echo ""

# 获取镜像名称
if [ -n "$1" ]; then
    IMAGE_NAME="$1"
else
    # 使用时间戳
    TIMESTAMP=$(date +%Y%m%d-%H%M%S)
    IMAGE_NAME="ysyx-dev-backup:${TIMESTAMP}"
fi

log_info "容器: ${CONTAINER_NAME}"
log_info "保存为: ${IMAGE_NAME}"
echo ""

# 检查容器是否存在
if ! podman ps -a --format '{{.Names}}' | grep -q "^${CONTAINER_NAME}$"; then
    echo "❌ 错误: 容器 ${CONTAINER_NAME} 不存在"
    exit 1
fi

# 确认
read -p "确认保存? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    log_info "已取消"
    exit 0
fi

# 显示容器信息
echo ""
log_info "容器状态:"
podman exec ${CONTAINER_NAME} bash -c "
echo '  用户: '$(whoami)' (UID: '$(id -u)')'
echo '  Shell: '$(echo \$SHELL)
echo '  家目录: '$(HOME)
echo '  工作目录: '$(pwd)
echo ''
echo '  已安装的工具:'
which gcc make cmake git python3 2>/dev/null | sed 's/^/    /'
echo ''
echo '  自定义配置:'
[ -f ~/.bashrc.local ] && echo '    ~/.bashrc.local 存在' || echo '    ~/.bashrc.local 不存在'
[ -f ~/.tmux.conf ] && echo '    ~/.tmux.conf 存在' || echo '    ~/.tmux.conf 不存在'
"
echo ""

# 提交镜像
log_info "正在保存..."
podman commit ${CONTAINER_NAME} ${IMAGE_NAME}

echo ""
log_success "保存成功！"
echo ""
echo "使用方法:"
echo "  # 查看镜像"
echo "  podman images | grep ${IMAGE_NAME%:*}"
echo ""
echo "  # 使用此镜像创建新容器"
echo "  podman run --name ysyx-dev-new \\"
echo "    -v \$(pwd):/home/sealessland/ysyx-workbench:Z \\"
echo "    ${IMAGE_NAME}"
echo ""
echo "  # 更新默认镜像"
echo "  podman tag ${IMAGE_NAME} ysyx-dev-ready:latest"
echo ""
echo "========================================="
