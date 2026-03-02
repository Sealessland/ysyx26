#!/bin/bash
# 容器环境初始化脚本
# 在容器内首次启动后运行此脚本，安装所有必要的开发工具

set -e

echo "========================================="
echo "一生一芯项目 - 容器环境初始化"
echo "========================================="

# 检查是否为 root 用户
if [ "$EUID" -eq 0 ]; then
    echo "检测到 root 用户，开始配置..."

    # 更新包列表
    echo "→ 更新包列表..."
    apt update

    # 安装 sudo
    echo "→ 安装 sudo..."
    apt install -y sudo

    # 获取环境变量
    USER_NAME=${USER:-sealessland}
    USER_UID=${USER_UID:-1000}

    echo "→ 创建用户: ${USER_NAME} (UID: ${USER_UID})..."

    # 创建用户
    if ! id "${USER_NAME}" &>/dev/null; then
        useradd -m -s /bin/bash -u ${USER_UID} ${USER_NAME}
        echo "✓ 用户创建成功"
    else
        echo "✓ 用户已存在"
    fi

    # 添加到 sudo 组
    usermod -aG sudo ${USER_NAME}

    # 配置 sudo 免密码
    echo "${USER_NAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER_NAME}
    chmod 440 /etc/sudoers.d/${USER_NAME}

    echo "✓ 用户配置完成"
    echo ""
    echo "========================================="
    echo "请运行以下命令切换到普通用户:"
    echo "  su - ${USER_NAME}"
    echo "  cd /home/${USER_NAME}/ysyx-workbench"
    echo "  bash init-container.sh"
    echo "========================================="

else
    echo "检测到普通用户，开始安装开发工具..."

    # 更新包列表
    echo "→ 更新包列表..."
    sudo apt update

    # 安装基础开发工具
    echo "→ 安装基础开发工具..."
    sudo apt install -y \
        build-essential \
        gcc \
        g++ \
        make \
        cmake \
        git \
        wget \
        curl \
        vim \
        gdb \
        python3 \
        python3-pip \
        libSDL2-dev \
        libreadline-dev \
        flex \
        bison \
        python3-pyelftools \
        libncurses5-dev \
        libncursesw5-dev

    # 安装 32 位支持库
    echo "→ 安装 32 位支持库..."
    sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install -y gcc-multilib g++-multilib || echo "警告: 32 位库安装失败，可能不影响使用"

    # 配置 Git
    echo "→ 配置 Git..."
    read -p "请输入你的名字: " GIT_NAME
    read -p "请输入你的邮箱: " GIT_EMAIL
    git config --global user.name "${GIT_NAME}"
    git config --global user.email "${GIT_EMAIL}"

    echo ""
    echo "========================================="
    echo "✓ 环境初始化完成！"
    echo "========================================="
    echo ""
    echo "已安装的工具:"
    echo "  - GCC/G++ (C/C++ 编译器)"
    echo "  - Make, CMake (构建工具)"
    echo "  - Git (版本控制)"
    echo "  - GDB (调试器)"
    echo "  - Python3 及相关工具"
    echo "  - SDL2 库 (图形支持)"
    echo "  - NEMU 相关依赖"
    echo ""
    echo "下一步操作:"
    echo "  cd nemu"
    echo "  make menuconfig  # 配置编译选项"
    echo "  make             # 编译 NEMU"
    echo ""
    echo "或初始化其他子项目:"
    echo "  cd .."
    echo "  bash init.sh abstract-machine"
    echo "  bash init.sh navy-apps"
    echo "  等等..."
    echo ""
    echo "详细教程请查看: docker-tutorial.md"
    echo "========================================="
fi
