#!/bin/sh

# 获取系统语言环境 | Get system locale
LANG=$(locale | grep LANGUAGE | cut -d  "=" -f 2 | cut -d "_" -f 1)
if [ "$LANG" != "zh" ] ; then
    LANG="en"
fi

# 中文符号支持 | Support special Chinese characters 
export LC_ALL=zh_CN.UTF-8

# 翻译文本 | Translation variables
readonly TIP_zh="即将删除已有的显卡配置文件并重置......"
readonly TIP_en="Preparing to delete graphics.conf and reset WORKSPACE..."
readonly TITLE_zh="警告 — DDE Dock"
readonly TITLE_en="Warning — DDE Dock"
readonly TEXT_zh="未检测到 NVIDIA 显卡驱动，插件无法正常切换显卡。建议安装 NVIDIA 闭源驱动！"
readonly TEXT_en="NVIDIA X driver not detected. Plugin won't work properly. Suggest installing nvidia-driver first!"

eval "TIP=\$TIP_${LANG}"
eval "TITLE=\$TITLE_${LANG}"
eval "TEXT=\$TEXT_${LANG}"

# 提示文字 | Tip
echo $TIP

# 删除权限错误的 WORKSPACE 并重建 | Delete WORKSPACE and rebuild
rm -rf ~/.config/dde-dock-graphics-plugin/

sh /opt/apps/dde-dock-graphics-plugin/files/bin/CheckConf.sh

# 判断 NVIDIA 闭源驱动 是否安装 | Judge whether nvidia-driver is installed
lshw -c video | grep "driver=nvidia" > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=500 --title="$TITLE" --text="$TEXT"
    echo "$TITLE: $TEXT"
    echo -n "Intel" | tee $WORKSPACE/graphics.conf > /dev/null
    exit
fi
