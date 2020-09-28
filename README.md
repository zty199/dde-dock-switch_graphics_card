# dde-dock-graphics-plugin (forked from mywhat/DDESwitchCard)

## 功能介绍

由论坛大佬 chanforever 的插件修改得来，在 Deepin dock栏 添加插件实现快速切换显卡的操作。

【原贴地址： https://bbs.deepin.org/forum.php?mod=viewthread&tid=197280 】

【github原项目地址： https://github.com/mywhat/DDESwitchCard/ 】

修改了整个代码结构，优化函数调用逻辑，取消了外部储存配置文件，避免被修改而影响插件显示。

自动检测是否安装 NVIDIA 显卡驱动，避免切换后因为没有驱动导致无法进入图形界面。

添加了 Rescue.sh 脚本，如果切换后无法进入图形界面可以运行该脚本删除相关配置文件并重启 lightdm 服务。

添加了 nvidia-prime 的配置，Intel 显卡状态下使用 prime-run 命令即可调用 N卡（需要高版本 xserver-xorg 支持）。

添加了 桌面右键菜单，可以快速调用 prime-run 运行 可执行文件 以及 桌面快捷方式。

添加了 插件右键菜单，支持手动刷新显卡信息，快速访问 系统显示器设置 以及 NVIDIA 显卡设置。

添加了 pkexec 策略文件，切换显卡授权提示框显示更美观。

添加了英文翻译，非中文环境自动显示英文。（能力有限，只能翻译英文了......）

## 编译环境依赖

qt-default

qtcreator（推荐使用 Qt Creator 直接打开 CMakeLists.txt 编译运行）

cmake, gcc, g++

libqt5core5a

libqt5gui5

libqt5widgets5

libdtkcore-dev

libdtkgui-dev

libdtkwidget-dev

dde-dock-dev


mesa-utils（运行时依赖）

zenity（运行时依赖）

## 源码编译

运行 build.sh 自动编译源码，并生成 dde-dock-graphics-plugin_"$version"_amd64.deb

## 使用

P.S.建议使用自动生成的 deb 安装包进行安装

1.  将 scripts 文件夹下 Initialize.sh，Intel,sh，NVIDIA.sh，CheckConf.sh，ResetConf.sh，Rescue.sh 放置在 /opt/apps/dde-dock-graphics-plugin/files/bin 文件夹下；将 icons 文件夹放置在 /opt/apps/dde-dock-graphics-plugin/files/share 文件夹下。

2.  将编译生成的 libswitch_graphics_card.so 放在 ~/.local/lib/dde-dock/plugins/ 或者 /usr/lib/dde-dock/plugins/ 文件夹下。

3.  等待 dde-dock 自动重新加载，即可在最右侧看到该插件已启用。该插件默认启用，可以选择手动禁用。

4.  将 prime-run.desktop 放入 /usr/share/deepin/dde-file-manager/oem-menuextensions/ ，可以在右键菜单中快速调用 prime-run 运行可执行文件。

## 感谢

linuxdeepin 官方的 dde-dock 项目仓库       https://github.com/linuxdeepin/dde-dock

linuxdeepin 官方的 dde-file-manager 项目仓库       https://github.com/linuxdeepin/dde-file-manager

GitHub 开源项目 dde-appknitter 的脚本翻译方式      https://github.com/Dziban-dev/dde-appknitter

论坛大佬 chanforever 的插件        https://bbs.deepin.org/forum.php?mod=viewthread&tid=197280

论坛大佬 jfy_99 的显卡切换脚本     https://bbs.deepin.org/forum.php?mod=viewthread&tid=192750

论坛大佬 risez 的 nvidia-prime 方案        https://bbs.deepin.org/forum.php?mod=viewthread&tid=191741

论坛大佬 q77190858 的 dde-dock系统监控小插件        https://bbs.deepin.org/forum.php?mod=viewthread&tid=179425

论坛大佬 shenmo，lenke，mmlmonkey，xuey 等提供的修改建议       https://bbs.deepin.org/forum.php?mod=viewthread&tid=197367

码云组织　Deepin开源项目　提供的 UOS 打包规范和方法
