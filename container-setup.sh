#!/bin/bash
# 容器内环境优化脚本
# 在容器内运行此脚本以优化长期开发体验
# 使用方法: ./dev.sh 进入容器后，执行 bash /home/sealessland/ysyx-workbench/container-setup.sh

set -e

echo "========================================="
echo "容器开发环境优化"
echo "========================================="
echo ""

# 1. 安装 tmux (用于持久会话)
echo "→ 检查 tmux..."
if ! command -v tmux &> /dev/null; then
    echo "  安装 tmux..."
    sudo apt update
    sudo apt install -y tmux ccache
    echo "  ✓ tmux 已安装"
else
    echo "  ✓ tmux 已存在"
fi

# 2. 配置 Shell 别名
echo "→ 配置 Shell 别名..."
cat >> ~/.bashrc << 'EOF'

# NEMU 开发别名
alias m='make CONFIG_ISA=riscv32 CONFIG_ENGINE=interpreter'
alias mr='make run'
alias n='./build/riscv32-nemu-interpreter'
alias mc='make clean'
alias md='make distclean'

# 并行编译（使用所有CPU核心）
alias mj='make -j$(nproc) CONFIG_ISA=riscv32 CONFIG_ENGINE=interpreter'

# 快速导航
alias ncd='cd /home/sealessland/ysyx-workbench/nemu'
alias pcd='cd /home/sealessland/ysyx-workbench'
EOF
echo "  ✓ 别名已添加到 ~/.bashrc"

# 3. 配置 Git
echo "→ 配置 Git..."
if [ -z "$(git config --global user.name)" ]; then
    read -p "  请输入你的名字: " GIT_NAME
    git config --global user.name "$GIT_NAME"
else
    echo "  ✓ Git 用户名已配置: $(git config --global user.name)"
fi

if [ -z "$(git config --global user.email)" ]; then
    read -p "  请输入你的邮箱: " GIT_EMAIL
    git config --global user.email "$GIT_EMAIL"
else
    echo "  ✓ Git 邮箱已配置: $(git config --global user.email)"
fi

git config --global color.ui true
git config --global core.editor vim
echo "  ✓ Git 配置完成"

# 4. 配置 tmux
echo "→ 配置 tmux..."
cat > ~/.tmux.conf << 'EOF'
# 设置前缀为 Ctrl+A
unbind C-b
set -g prefix C-a

# 启用鼠标
set -g mouse on

# 设置窗口和面板索引从 1 开始
set -g base-index 1
setw -g pane-base-index 1

# 重新加载配置
bind r source-file ~/.tmux.conf \; display-message "Config reloaded"

# 分割窗口
bind v split-window -h -c "#{pane_current_path}"
bind s split-window -v -c "#{pane_current_path}"

# 切换面板
bind -n M-Left select-pane -L
bind -n M-Right select-pane -R
bind -n M-Up select-pane -U
bind -n M-Down select-pane -D
EOF
echo "  ✓ tmux 配置已创建"

# 5. 创建工作目录快捷方式
echo "→ 创建工作目录快捷方式..."
ln -sf /home/sealessland/ysyx-workbench ~/workspace
echo "  ✓ 快捷方式已创建: ~/workspace"

# 6. 配置 ccache（如果已安装）
if command -v ccache &> /dev/null; then
    echo "→ 配置 ccache..."
    export CC="gcc"
    export CXX="g++"
    export USE_CCACHE=1

    ccache -M 50G 2>/dev/null || true
    echo "  ✓ ccache 已配置"
fi

echo ""
echo "========================================="
echo "✓ 优化完成！"
echo "========================================="
echo ""
echo "已配置的功能:"
echo "  - tmux: 持久化会话"
echo "  - 别名: m(编译), mr(运行), n(直接运行), mc(清理)"
echo "  - Git: 用户信息"
echo "  - tmux: 优化的配置"
echo "  - 快捷方式: ~/workspace"
echo "  - ccache: 编译缓存"
echo ""
echo "下一步:"
echo "  1. 重新加载配置: source ~/.bashrc"
echo "  2. 或退出重新进入: exit && ./dev.sh"
echo "  3. 使用 tmux: tmux new -s work"
echo "  4. 使用别名: m (编译), mr (运行)"
echo ""
echo "========================================="
