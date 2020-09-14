#!/bin/sh

# 删除 xorg.conf
sudo rm /etc/X11/xorg.conf.bak /etc/X11/xorg.conf

# 删除 prime-run
sudo rm /usr/bin/prime-run.bak /usr/bin/prime-run
sudo rm /usr/share/deepin/dde-file-manager/oem-menuextensions/prime-run.desktop

# 删除 nvidia-graphics-drivers.conf
sudo rm /etc/modprobe.d/nvidia-graphics-driver.conf.bak /etc/modprobe.d/nvidia-graphics-driver.conf

# 删除 display_setup.sh
sudo rm /etc/lightdm/display_setup.sh

# 恢复 lightdm.conf
sudo sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' /etc/lightdm/lightdm.conf

# 重启 lightdm
sudo service lightdm restart
