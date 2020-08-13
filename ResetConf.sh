#!/bin/sh

# 提示文字
echo "即将删除已有的显卡配置文件并重置......"

# 删除权限错误的 WORKSPACE 并重建
rm -rf ~/.config/dde-dock-switch_graphics_card/

sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh

# 判断 NVIDIA 闭源驱动 是否安装
lshw -c video | grep "driver=nvidia" > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=300 --title="警告—DDE Dock" --text="未检测到 NVIDIA 显卡驱动，插件无法正常切换显卡。建议安装 NVIDIA 闭源驱动！"
    echo -n "Intel" | tee $WORKSPACE/graphics.conf > /dev/null
    exit
fi
