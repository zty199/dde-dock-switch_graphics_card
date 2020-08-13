#!/bin/sh

# 检查并初始化 WORKSPACE
if [ ! -d $HOME/.config/dde-dock-switch_graphics_card/ ]
then
	mkdir -p $HOME/.config/dde-dock-switch_graphics_card/
fi

WORKSPACE=$HOME/.config/dde-dock-switch_graphics_card/

# 生成 graphics.conf
glxinfo | grep "OpenGL vendor" | grep "NVIDIA" > /dev/null
if [ $? -ne 0 ]
then
	echo -n "Intel" | tee $WORKSPACE/graphics.conf > /dev/null
else
	echo -n "NVIDIA" | tee $WORKSPACE/graphics.conf > /dev/null
fi
