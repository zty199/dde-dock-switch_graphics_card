#!/bin/sh

# 提示文字
echo "即将删除已有的显卡配置文件并重置......"

# 删除权限错误的 WORKSPACE 并重建
rm -rf ~/.config/dde-dock-switch_graphics_card/
sh /opt/durapps/dde-dock-switch_graphics_card/CheckConf.sh
