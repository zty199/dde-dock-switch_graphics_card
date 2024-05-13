#!/bin/sh

TITLE="Warning — DDE Dock"
TEXT1="NVIDIA X driver not detected, suggest installing nvidia-driver first"
TEXT2="NVIDIA graphics is already in use"
TIP="Preparing to switch graphics card and logout, please save your work in progress in time"

# 翻译文本 | Translation variables
case "${LANGUAGE:-$LANG}" in
es*)
	TITLE="Advertencia - Muelle DDE"
	TEXT1="No se los detectan los controladores gráficos NVIDIA, se recomienda instalar primero nvidia-driver"
	TEXT2="Ya se utilizan gráficos NVIDIA"
	TIP="Preparándose para cambiar la tarjeta gráfica y cerrar la sesión, guarde el progreso de su trabajo a tiempo"
	;;
zh*)
	export LC_ALL=zh_CN.UTF-8 # 中文符号支持 | Support special Chinese characters
	TITLE="警告 — DDE Dock"
	TEXT1="未检测到 NVIDIA 显卡驱动，建议安装 NVIDIA 闭源驱动"
	TEXT2="已经是 NVIDIA 显卡了"
	TIP="即将切换显卡并注销登录，请及时保存您的工作进度"
	;;
esac

# 判断 NVIDIA 闭源驱动 是否安装 | Judge whether nvidia-driver is installed
lshw -c video | grep "driver=nvidia" >/dev/null
if [ $? -ne 0 ]; then
	# zenity --warning --width=500 --title="$TITLE" --text="$TEXT1"
	notify-send "$TITLE" -t 5000 -a dde-dock-graphics-plugin -i dialog-warning "$TEXT1"
	echo "$TITLE: $TEXT1"
	exit
fi

# 判断当前显卡状态 | Judge which graphics card is being used
glxinfo | grep "OpenGL vendor" | grep "NVIDIA" >/dev/null
if [ $? -eq 0 ]; then
	# zenity --warning --width=300 --title="$TITLE" --text="$TEXT2"
	notify-send "$TITLE" -t 2000 -a dde-dock-graphics-plugin -i dialog-warning "$TEXT2"
	echo "$TITLE: $TEXT2"
	exit
fi

# 提示文本 | Tip
echo "$TIP"

# 初始化 NVIDIA 相关配置文件 | Initialize
sh /opt/apps/dde-dock-graphics-plugin/files/bin/Initialize.sh

# 禁用 nvidia-prime | Disable nvidia-prime
sudo rm /usr/bin/prime-run
sudo rm /usr/share/deepin/dde-file-manager/oem-menuextensions/prime-run.desktop

# 修改 xorg.conf | Modify xorg.conf
sudo cp /etc/X11/xorg.conf.bak /etc/X11/xorg.conf
sudo sed -i 's$Screen      0  "Screen0" 0 0$Screen      0  "DGPU" 0 0$g' /etc/X11/xorg.conf
sudo sed -i 's$\n    Option         "AllowNVIDIAGPUScreens"$$g' /etc/X11/xorg.conf

# 启用 nvidia-graphics-drivers.conf | Enable nvidia-graphics-drivers.conf
sudo mv /etc/modprobe.d/nvidia-graphics-driver.conf.bak /etc/modprobe.d/nvidia-graphics-driver.conf

# 修改 lightdm.conf | Modify lightdm.conf
sudo sed -i 's$#display-setup-script=$display-setup-script=/etc/lightdm/display_setup.sh$g' /etc/lightdm/lightdm.conf

# 重启 lightdm | Restart lightdm
sudo service lightdm restart
