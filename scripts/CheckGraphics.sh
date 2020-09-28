#!/bin/sh

# 获取系统语言环境 | Get system locale
LANG=$(locale | grep LANGUAGE | cut -d '=' -f 2 | cut -d '_' -f 1)
if [ "$LANG" != "zh" ] ; then
    LANG="en"
fi

# 中文符号支持 | Support special Chinese characters 
export LC_ALL=zh_CN.UTF-8

# 翻译文本 | Translation variables
readonly TITLE_zh="警告 — DDE Dock"
readonly TITLE_en="Warning — DDE Dock"
readonly TEXT_zh="未检测到 NVIDIA 显卡驱动，插件无法正常切换显卡。建议安装 NVIDIA 闭源驱动！"
readonly TEXT_en="NVIDIA X driver not detected. Plugin won't work properly. Suggest installing nvidia-driver first!"

eval "TITLE=\$TITLE_${LANG}"
eval "TEXT=\$TEXT_${LANG}"

# 判断 NVIDIA 闭源驱动 是否安装 | Judge whether nvidia-driver is installed
lshw -c video | grep "driver=nvidia" > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=500 --title="$TITLE" --text="$TEXT"
    echo "Intel"
    exit
fi

# 获取当前显卡信息 | Get current graphics card info
glxinfo | grep "OpenGL vendor" | grep "NVIDIA" > /dev/null
if [ $? -ne 0 ]
then
	echo "Intel"
    exit
else
	echo "NVIDIA"
    exit
fi
