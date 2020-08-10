#!/bin/sh

# 提示文字
echo "即将删除已有的显卡配置文件并重置......"

# 删除权限错误的 WORKSPACE 并重建
rm -rf ~/.config/dde-dock-switch_graphics_card/

sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh

# 判断 nvidia-smi 是否安装
which nvidia-smi > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=300 --title="警告—DDE Dock" --text="未检测到 nvidia-smi，插件无法正常切换显卡。请检查是否安装 NVIDIA 闭源驱动！"
    echo -n "Intel" > $WORKSPACE/graphics.conf
    exit
fi
