#!/usr/bin/env bash
# ${BASH_SOURCE[0]} /home/book/work/private-node/docker/scripts/monitor_docker_run.sh
# dirname "${BASH_SOURCE[0]}"  /home/book/work/private-node/docker/scripts/
# cd "$( dirname "${BASH_SOURCE[0]}" )/../..  /home/book/work/private-node
# MONITOR_HOME_DIR = /home/book/work/private-node  work/

MONITOR_HOME_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

display=""
if [ -z ${DISPLAY} ];then
    display=":1"
else
    display="${DISPLAY}"
fi

# display=""：初始化一个名为 display 的变量，值为空字符串
# -z 表示检查字符串是否为空。${DISPLAY} 是环境变量 DISPLAY 的值
# display=":1"：如果 DISPLAY 为空，将 display 设置为 :1
# display="${DISPLAY}"：将 display 设置为 DISPLAY 的值

local_host="$(hostname)"
user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"

# 使用 hostname 命令获取本地主机名  使用特殊环境变量 ${USER} 获取当前用户的用户名
# 使用 id -u 命令获取当前用户的用户 ID（UID）  使用 id -g -n 命令获取当前用户所属的主组名


echo "stop and rm docker" 
docker stop linux_monitor > /dev/null
docker rm -v -f linux_monitor > /dev/null

# 输出一条消息，提示正在停止和删除 Docker 容器
# 使用 docker stop 命令停止名为 linux_monitor 的 Docker 容器，并将标准输出重定向到 /dev/null，以忽略命令的输出。
# /dev/null 是一个特殊的设备文件，所有写入该文件的数据都会被丢弃，因此可以用来屏蔽命令的输出
# 使用 docker rm 命令删除名为 linux_monitor 的 Docker 容器，并使用 -v 选项删除关联的卷，使用 -f 选项强制删除容器，即使它正在运行

echo "start docker"
docker run -it -d \
--name linux_monitor \
-e DISPLAY=$display \
--privileged=true \
-e DOCKER_USER="${user}" \
-e USER="${user}" \
-e DOCKER_USER_ID="${uid}" \
-e DOCKER_GRP="${group}" \
-e DOCKER_GRP_ID="${gid}" \
-e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
-v ${MONITOR_HOME_DIR}:/work \
-v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
--net host \
linux:monitor

# -it 参数表示以交互模式运行容器
# -v ${MONITOR_HOME_DIR}:/work: 这个选项将主机上的 ${MONITOR_HOME_DIR} 目录挂载到容器中的 /work 目录
# 在容器内部，可以通过 /work 目录访问主机上的文件或目录，对其进行读写操作。
# 这种挂载方式可以用于在容器中访问主机上的数据或配置文件，或者将容器中生成的数据保存到主机上的持久存储中
# ${MONITOR_HOME_DIR}:/work   /home/book/work/private-node  work/
# -v -e 挂载 环境变量
# --net host: 这个选项告诉 Docker 使用主机的网络命名空间。
# 这意味着容器将共享主机的网络配置，包括网络接口、IP 地址和端口映射等。在容器内部，可以直接访问主机上的网络服务，并且容器内部的网络配置与主机相同