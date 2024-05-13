#!/bin/sh

TITLE="Warning — DDE Dock"
TEXT="NVIDIA X driver not detected, suggest installing nvidia-driver first"

# 翻译文本 | Translation variables
case "${LANGUAGE:-$LANG}" in
es*)
	TITLE="Advertencia - Muelle DDE"
	TEXT="No se los detectan los controladores gráficos NVIDIA, se recomienda instalar primero nvidia-driver"
	;;
zh*) export LC_ALL=zh_CN.UTF-8 # 中文符号支持 | Support special Chinese characters
	TITLE="警告 — DDE Dock"
	TEXT="未检测到 NVIDIA 显卡驱动，建议安装 NVIDIA 闭源驱动"
	;;
esac

# 判断 NVIDIA 闭源驱动 是否安装 | Judge whether nvidia-driver is installed
lshw -c video 2>/dev/null | grep "driver=nvidia" >/dev/null
if [ $? -ne 0 ]; then
	# zenity --warning --width=500 --title="$TITLE" --text="$TEXT"
	notify-send "$TITLE" -t 5000 -a dde-dock-graphics-plugin -i dialog-warning "$TEXT"
	echo "Intel"
	exit
fi

# 获取当前显卡信息 | Get current graphics card info
glxinfo | grep "OpenGL vendor" | grep "NVIDIA" >/dev/null
if [ $? -ne 0 ]; then
	echo "Intel"
	exit
else
	echo "NVIDIA"
	exit
fi
