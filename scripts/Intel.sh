#!/bin/sh

# 获取系统语言环境 | Get system locale
LANG=$(locale | grep LANGUAGE | cut -d "=" -f 2 | cut -d "_" -f 1)
if [ "$LANG" != "zh" ] ; then
    LANG="en"
fi
# 中文符号支持 | Support special Chinese characters 
export LC_ALL=zh_CN.UTF-8

# 翻译文本 | Translation variables
readonly TITLE_zh="警告 — DDE Dock"
readonly TITLE_en="Warning — DDE Dock"
readonly TEXT1_zh="未检测到 NVIDIA 显卡驱动，插件无法正常切换显卡。建议安装 NVIDIA 闭源驱动！"
readonly TEXT1_en="NVIDIA X driver not detected. Plugin won't work properly. Suggest installing nvidia-driver first!"
readonly TEXT2_zh="已经是 Intel 显卡了！"
readonly TEXT2_en="Intel graphics is already in use!"
readonly TIP_zh="即将切换至 Intel 显卡。在注销登录之前，请保存好当前的工作。"
readonly TIP_en="Preparing to switch to Intel graphics. Please save your data before logout."

eval "TITLE=\$TITLE_${LANG}"
eval "TEXT1=\$TEXT1_${LANG}"
eval "TEXT2=\$TEXT2_${LANG}"
eval "TIP=\$TIP_${LANG}"

# 判断 NVIDIA 闭源驱动 是否安装 | Judge whether nvidia-driver is installed
lshw -c video | grep "driver=nvidia" > /dev/null
if [ $? -ne 0 ]
then
	zenity --warning --width=500 --title="$TITLE" --text="$TEXT1"
    echo "$TITLE: $TEXT1"
    exit
fi

# 判断当前显卡状态 | Judge which graphics card is being used
glxinfo | grep "OpenGL vendor" | grep "Intel" > /dev/null
if [ $? -eq 0 ]
then
	zenity --warning --width=300 --title="$TITLE" --text="$TEXT2"
    echo "$TITLE: $TEXT2"
    exit
fi

# 提示文本 | Tip
echo $TIP

# 初始化 nvidia-prime 相关配置文件 | Initialize
sh /opt/apps/dde-dock-graphics-plugin/files/bin/Initialize.sh

# 启用 nvidia-prime | Enable nvidia-prime
sudo ln -s -f /opt/apps/dde-dock-graphics-plugin/files/bin/prime-run.sh /usr/bin/prime-run
sudo ln -s -f /opt/apps/dde-dock-graphics-plugin/files/share/oem-menuextensions/prime-run.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/

# 修改 xorg.conf | Modify xorg.conf
sudo cp /etc/X11/xorg.conf.bak /etc/X11/xorg.conf
sudo sed -i 's$Screen      0  "Screen0" 0 0$Screen      0  "IGPU" 0 0$g' /etc/X11/xorg.conf

# 移除 nvidia-graphics-drivers.conf | Remove nvidia-graphics-drivers.conf
sudo mv /etc/modprobe.d/nvidia-graphics-driver.conf /etc/modprobe.d/nvidia-graphics-driver.conf.bak

# 恢复 lightdm.conf | Restore lightdm.conf
sudo sed -i 's$display-setup-script=/etc/lightdm/display_setup.sh$#display-setup-script=$g' /etc/lightdm/lightdm.conf

# 重启 lightdm | Restart lightdm
sudo service lightdm restart
