#!/bin/sh

# 提示文本
echo "即将切换至 Intel 显卡。在注销登录之前，请保存好当前的工作。"

# 修改 xorg.conf
sudo cp /etc/X11/xorg.conf.bak /etc/X11/xorg.conf
sudo sed -i 's$Screen      0  "Screen0" 0 0$Screen      0  "IGPU" 0 0$g' /etc/X11/xorg.conf

# 移除 nvidia-graphics-drivers.conf
sudo mv /etc/modprobe.d/nvidia-graphics-driver.conf /etc/modprobe.d/nvidia-graphics-driver.conf.bak

# 恢复 lightdm.conf
sudo sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' /etc/lightdm/lightdm.conf

# 更新 graphics.conf
echo -n "Intel" | sudo tee $HOME/.config/dde-dock-switch_graphics_card/graphics.conf > /dev/null

# 重启 lightdm
sudo service lightdm restart
