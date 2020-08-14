#!/bin/sh

# 提示文字
echo "即将初始化 NVIDIA 显卡相关配置文件......"

# 获取显卡 BusID
# 仅获取第一张 NVIDIA 显卡的 PCI 设备地址
NVIDIA_BusID=`lspci | egrep 'VGA|3D' | grep 'NVIDIA' | cut -d ' ' -f 1 | sed -r 's/0?(.)/\1/' | sed -e 's/:0/:/g' -e 's/\./:/g' | head -n 1`

Intel_BusID=`lspci | egrep 'VGA|3D' | grep 'Intel' | cut -d ' ' -f 1 | sed -r 's/0?(.)/\1/' | sed -e 's/:0/:/g' -e 's/\./:/g'`

# 生成 xorg.conf
echo '# dde-dock-switch_graphics_card: X configuration file generated by dde-dock-plugins
# dde-dock-switch_graphics_card: version 1.4

Section "ServerLayout"
    Identifier     "Layout0"
    Screen      0  "Screen0" 0 0
    Option         "AllowNVIDIAGPUScreens"
EndSection

Section "Module"
	Load "modesetting"
EndSection

Section "Device"
    Identifier     "GFX0"
    Driver         "modesetting"
    VendorName     "Intel Corporation"
    BusID          "PCI:'$Intel_BusID'"
EndSection

Section "Device"
    Identifier     "PEGP"
    Driver         "nvidia"
    VendorName     "NVIDIA Corporation"
    BusID          "PCI:'$NVIDIA_BusID'"
EndSection

Section "Screen"
    Identifier     "IGPU"
    Device         "GFX0"
    DefaultDepth    24
    SubSection     "Display"
        Depth       24
    EndSubSection
EndSection

Section "Screen"
    Identifier     "DGPU"
    Device         "PEGP"
    DefaultDepth    24
    Option         "AllowEmptyInitialConfiguration"
    SubSection     "Display"
        Depth       24
    EndSubSection
EndSection' | sudo tee /etc/X11/xorg.conf.bak > /dev/null

# 生成 nvidia-graphics-drivers.conf
echo 'options nvidia-drm modeset=1' | sudo tee /etc/modprobe.d/nvidia-graphics-driver.conf.bak > /dev/null

# 生成 display_setup.sh
echo '#!/bin/sh
xrandr --setprovideroutputsource modesetting NVIDIA-0
xrandr --auto
xrandr --dpi 96' | sudo tee /etc/lightdm/display_setup.sh > /dev/null
sudo chmod +x /etc/lightdm/display_setup.sh

# 生成 prime-run
echo '#!/bin/sh
file=$1
if [ "${file##*.}"x = "desktop"x ]
then
    __NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $(cat $file | grep "Exec=" | sed "s/^Exec=//" | head -n 1)
else
    __NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $file
fi' | sudo tee /usr/bin/prime-run.bak > /dev/null
sudo chmod +x /usr/bin/prime-run.bak
