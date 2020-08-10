#!/bin/sh

# 判断 nvidia-smi 是否安装
which nvidia-smi > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=300 --title="警告—DDE Dock" --text="未检测到 nvidia-smi，无法切换到 NVIDIA 显卡。请检查是否安装 NVIDIA 闭源驱动！"
    exit
fi

# 判断当前显卡状态
nvidia-smi | grep kwin > /dev/null
if [ $? -eq 0 ]
then
	zenity --warning --width=150 --title="警告—DDE Dock" --text="已经是 NVIDIA 显卡了！"
    exit
fi

# 提示文本
echo '即将切换至 NVIDIA 显卡。在注销登录之前，请保存好当前的工作。'

# 初始化 NVIDIA 相关配置文件
/opt/durapps/dde-dock-switch_graphics_card/Initialize.sh

# 修改 xorg.conf
sudo cp /etc/X11/xorg.conf.bak /etc/X11/xorg.conf
sudo sed -i 's$Screen      0  "Screen0" 0 0$Screen      0  "DGPU" 0 0$g' /etc/X11/xorg.conf
sudo sed -i 's$\n    Option         "AllowNVIDIAGPUScreens"$$g' /etc/X11/xorg.conf

# 启用 nvidia-graphics-drivers.conf
sudo mv /etc/modprobe.d/nvidia-graphics-driver.conf.bak /etc/modprobe.d/nvidia-graphics-driver.conf

# 修改 lightdm.conf
sudo sed -i 's$#display-setup-script=$display-setup-script=/etc/lightdm/display_setup.sh$g' /etc/lightdm/lightdm.conf

# 重启 lightdm
sudo service lightdm restart
