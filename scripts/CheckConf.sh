#!/bin/sh

# 检查并初始化 WORKSPACE | Check and initialize WORKSPACE
if [ ! -d $HOME/.config/dde-dock-graphics-plugin/ ]
then
	mkdir -p $HOME/.config/dde-dock-graphics-plugin/
fi

WORKSPACE=$HOME/.config/dde-dock-graphics-plugin/

# 获取系统语言环境 | Get system locale
LANG=$(locale | grep LANGUAGE | cut -d  "=" -f 2 | cut -d "_" -f 1)

echo -n $LANG | tee $WORKSPACE/locale.conf > /dev/null

# 生成 graphics.conf | Generate graphics.conf
glxinfo | grep "OpenGL vendor" | grep "NVIDIA" > /dev/null
if [ $? -ne 0 ]
then
	echo -n "Intel" | tee $WORKSPACE/graphics.conf > /dev/null
else
	echo -n "NVIDIA" | tee $WORKSPACE/graphics.conf > /dev/null
fi
