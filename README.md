# dde-dock-graphics-plugin (forked from mywhat/DDESwitchCard)

## 功能介绍

原贴地址：[切换显卡插件](https://bbs.deepin.org/zh/post/197280)

github 原项目地址：[mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard/)

<br/>

由论坛大佬 chanforever 的插件修改得来，在 dde-dock 添加插件实现快速切换显卡的操作。

<br/>

修改了整个代码结构，优化函数调用逻辑，取消了外部储存配置文件，避免被修改而影响插件显示。

自动检测是否安装 NVIDIA 显卡驱动，避免切换后因为没有驱动导致无法进入图形界面。

添加了 Rescue.sh 脚本，如果切换后无法进入图形界面可以运行该脚本删除相关配置文件并重启 lightdm 服务。

添加了 nvidia-prime 的配置，Intel 显卡状态下使用 prime-run 命令即可调用 N卡（需要高版本 xserver-xorg 支持）。

添加了 桌面右键菜单，可以快速调用 prime-run 运行 可执行文件 以及 桌面快捷方式。

添加了 插件右键菜单，支持手动刷新显卡信息，快速访问 系统显示器设置 以及 NVIDIA 显卡设置。

添加了 pkexec 策略文件，切换显卡授权提示框显示更美观。

添加了英文翻译，非中文环境自动显示英文。（能力有限，只能翻译英文了......）

适配 dde-dock (>= 5.4.7-1)。

## 编译环境依赖

qt5-default

qtcreator（推荐使用 Qt Creator 直接打开 CMakeLists.txt 编译运行）

cmake, gcc, g++

qt5-default

qttools5-dev

libdtkcore-dev

libdtkwidget-dev

dde-dock-dev

<br/>

mesa-utils（运行时依赖）

zenity（运行时依赖）

libnotify4（运行时依赖）

## 源码编译

运行 build.sh 自动编译源码，并生成 dde-dock-graphics-plugin_"$version"_amd64.deb

## 使用

* P.S.建议使用自动生成的 deb 安装包进行安装

1.  将 scripts 文件夹下所有 sh 脚本放置在 /opt/apps/dde-dock-graphics-plugin/files/bin 文件夹下。

2.  将编译生成的 libswitch-graphics-card.so 放在 ~/.local/lib/dde-dock/plugins/ 或者 /usr/lib/dde-dock/plugins/ 文件夹下。

3.  等待 dde-dock 自动重新加载，即可在最右侧看到该插件已启用。该插件默认启用，可以选择手动禁用。

4.  将 prime-run.desktop 放入 /usr/share/deepin/dde-file-manager/oem-menuextensions/ ，可以在右键菜单中快速调用 prime-run 运行可执行文件。

## 感谢

linuxdeepin 官方的 [dde-dock](https://github.com/linuxdeepin/dde-dock) 项目仓库

linuxdeepin 官方的 [dde-file-manager](https://github.com/linuxdeepin/dde-file-manager) 项目仓库

GitHub 开源项目 [dde-appknitter](https://github.com/Dziban-dev/dde-appknitter) 的脚本翻译方式

Github 开源项目 [dde-store](https://github.com/dekzi/dde-store) 的系统通知发送方式

GitHub 大佬 [xmuli](https://github.com/xmuli) 的 [Qt 项目(Cmake)设置国际化支持](https://ifmet.cn/posts/9644ed82/) 方法

论坛大佬 chanforever 的 [DDESwitchCard](https://github.com/mywhat/DDESwitchCard) 插件        https://bbs.deepin.org/zh/post/197280

论坛大佬 jfy_99 的显卡切换脚本     https://bbs.deepin.org/zh/post/192750

论坛大佬 risez 的 nvidia-prime 方案        https://bbs.deepin.org/zh/post/191741

论坛大佬 q77190858 的 [dde-sys-monitor-plugin](https://github.com/q77190858/dde-sys-monitor-plugin) 插件        https://bbs.deepin.org/zh/post/179425

论坛大佬 shenmo，lenke，mmlmonkey，xuey 等提供的修改建议       https://bbs.deepin.org/zh/post/197367

码云组织　[开源应用](https://gitee.com/deepin-opensource)　提供的 UOS 打包规范和方法
