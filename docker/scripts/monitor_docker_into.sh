#!/usr/bin/env bash

xhost +local:root 1>/dev/null 2>&1
docker exec \
    -u root \
    -it linux_monitor \
    /bin/bash
xhost -local:root 1>/dev/null 2>&1

# 使用 xhost 命令允许 root 用户使用本地的 X Window System 服务。+local:root 表示允许本地的 root 用户访问 X Window System
# -u root：这个选项指定了在容器中执行命令时要使用的用户，这里是 root 用户
# -it linux_monitor：这个参数指定了要在哪个容器中执行命令，这里是名为 linux_monitor 的容器
# xhost -local:root 1>/dev/null 2>&1：这行命令使用 xhost 命令禁止 root 用户使用本地的 X Window System 服务

# 整个脚本片段的目的是在 Docker 容器中以 root 用户身份打开一个交互式的 Bash 终端
# 并在执行前临时允许 root 用户访问 X Window System 服务，执行完毕后再禁止。

# 1>/dev/null 意味着将标准输出（STDOUT）重定向到 /dev/null，即丢弃输出。
# 2>&1 意味着将标准错误输出（STDERR）重定向到与标准输出相同的位置，也就是 /dev/null，这样可以确保不会有错误消息显示在终端上。