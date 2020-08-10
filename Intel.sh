#!/bin/sh

# 判断 nvidia-smi 是否安装
which nvidia-smi > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=300 --title="警告—DDE Dock" --text="未检测到 nvidia-smi，插件无法正常切换显卡。请检查是否安装 NVIDIA 闭源驱动！"
    exit
fi

# 判断当前显卡状态
nvidia-smi | grep kwin > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=150 --title="警告—DDE Dock" --text="已经是 Intel 显卡了！"
    exit
fi

# 提示文本
echo "即将切换至 Intel 显卡。在注销登录之前，请保存好当前的工作。"

# 初始化 nvidia-prime 相关配置文件
/opt/durapps/dde-dock-switch_graphics_card/Initialize.sh

# 启用 nvidia-prime
sudo mv /usr/bin/prime-run.bak /usr/bin/prime-run

# 修改 xorg.conf
sudo cp /etc/X11/xorg.conf.bak /etc/X11/xorg.conf
sudo sed -i 's$Screen      0  "Screen0" 0 0$Screen      0  "IGPU" 0 0$g' /etc/X11/xorg.conf

# 移除 nvidia-graphics-drivers.conf
sudo mv /etc/modprobe.d/nvidia-graphics-driver.conf /etc/modprobe.d/nvidia-graphics-driver.conf.bak

# 恢复 lightdm.conf
sudo sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' /etc/lightdm/lightdm.conf

# 重启 lightdm
sudo service lightdm restart
