#!/usr/bin/env bash

set -e
#让脚本在任何一个命令执行失败（返回非零退出状态码）时立即停止执行，并且返回该错误的退出状态码

cd "$(dirname "${BASH_SOURCE[0]}")"
#${BASH_SOURCE[0]}: 这个变量表示当前正在执行的 Bash 脚本文件的路径
#dirname: 这是一个命令，用于获取给定文件路径的目录部分
#$(...): 这个语法是 Bash 中的命令替换语法，它会执行括号中的命令，并用其输出结果替换整个表达式
#整个命令的作用是获取当前脚本文件的路径，然后使用 dirname 命令获取该路径的父目录，最后切换当前工作目录到该父目录

# https://github.com/abseil/abseil-cpp/archive/refs/tags/20200225.2.tar.gz
# Install abseil.
#获取当前系统的处理器核心数
THREAD_NUM=$(nproc)
VERSION="20200225.2"
PKG_NAME="abseil-cpp-${VERSION}.tar.gz"

tar xzf "${PKG_NAME}"
pushd "abseil-cpp-${VERSION}"
    mkdir build && cd build
    cmake .. \
        -DBUILD_SHARED_LIBS=ON \
        -DCMAKE_CXX_STANDARD=14 \
        -DCMAKE_INSTALL_PREFIX=/usr/local
    make -j${THREAD_NUM}
    make install
popd

#告诉 CMake 构建共享库（动态链接库）
#指定了 C++ 标准的版本，这里设置为 C++14
#指定了安装目录的前缀，即项目构建完成后的安装路径
#popd 命令用于将先前使用 pushd 命令入栈的目录弹出栈，并切换回到该目录。这个命令通常用于在脚本中进行目录切换的操作

ldconfig
#用于配置共享库运行时链接器
#ldconfig是一个动态链接库管理命令，其目的为了让动态链接库为系统所共享

# Clean up
rm -rf "abseil-cpp-${VERSION}" "${PKG_NAME}"