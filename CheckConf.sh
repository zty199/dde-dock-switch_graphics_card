#!/bin/sh

# 检查并初始化 WORKSPACE
if [ ! -d $HOME/.config/dde-dock-switch_graphics_card/ ]
then
	mkdir -p $HOME/.config/dde-dock-switch_graphics_card/
fi

WORKSPACE=$HOME/.config/dde-dock-switch_graphics_card/

# 生成 graphics.conf
nvidia-smi | grep kwin > /dev/null
if [ $? -ne 0 ]
then
	echo -n "Intel" > $WORKSPACE/graphics.conf
else
	echo -n "NVIDIA" > $WORKSPACE/graphics.conf
fi
