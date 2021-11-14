# dde-dock-graphics-plugin (forked from mywhat/DDESwitchCard)

原贴地址：[切换显卡插件](https://bbs.deepin.org/zh/post/197280)

GitHub 原项目地址：[mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard/)

## 功能介绍

由论坛大佬 chanforever 的插件修改得来，在 **dde-dock** 添加插件实现快速切换显卡的操作。

目前仅支持 **Intel + NVIDIA** 双显卡，且不支持独显直连功能的笔记本。

* **AMD + NVIDIA** 双显卡用户不推荐使用，如果使用后造成 xserver 无法启动，可在 tty2 中执行 `/opt/apps/dde-dock-graphics-plugin/files/bin/Rescue.sh` 还原插件修改。

## 功能优化

* 修改了整个代码结构，优化函数调用逻辑，取消了外部储存配置文件。

* 切换显卡前自动判断 **NVIDIA** 显卡驱动是否安装 。

* 添加 **Rescue.sh** 脚本，如果切换后无法进入图形界面可以运行该脚本删除相关配置文件并重启 lightdm 服务。

* 添加 **nvidia-prime** 相关配置，**Intel** 显卡状态下使用 **prime-run** 命令即可调用 **NVIDIA** 显卡运行指定程序。

* 添加了桌面右键菜单，可以直接调用 **prime-run** 运行 **可执行文件** 以及 **桌面快捷方式**。

* 添加了插件右键菜单，支持手动刷新显卡信息，快速访问 **显示器设置** 以及 **NVIDIA 显卡设置**。

* 添加了 **pkexec** 策略文件，切换显卡授权提示框显示更美观。

* 添加了英文翻译，非中文环境自动显示英文。（能力有限，只能翻译英文了......）

## 相关依赖

### 编译依赖

cmake

qt5-default

qttools5-dev

libgsettings-qt-dev

libdtkcore-dev

libdtkgui-dev

libdtkwidget-dev

libdframeworkdbus-dev

dde-dock-dev

qtcreator（推荐使用 Qt Creator 直接打开 CMakeLists.txt 编译运行）

```
sudo apt install cmake qt5-default qttools5-dev libgsettings-qt-dev libdtkcore-dev libdtkgui-dev libdtkwidget-dev libdframeworkdbus-dev dde-dock-dev qtcreator
```

### 运行依赖

mesa-utils

zenity

libnotify4

```
sudo apt install mesa-utils zenity libnotify4
```

## 源码编译

安装编译所需依赖后，进入项目目录，在终端中打开，执行 `fakeroot dpkg-buildpackage -b`

项目目录上层文件夹中将生成 `dde-dock-graphics-plugin_${version}_amd64.deb`，双击安装即可。

## 感谢

linuxdeepin 官方的 [dde-dock](https://github.com/linuxdeepin/dde-dock) 项目仓库

linuxdeepin 官方的 [dde-file-manager](https://github.com/linuxdeepin/dde-file-manager) 项目仓库

linuxdeepin 官方的 [dde-session-ui](https://github.com/linuxdeepin/dde-session-ui) 项目仓库

GitHub 开源项目 [dde-appknitter](https://github.com/Dziban-dev/dde-appknitter) 的脚本翻译方式

Github 开源项目 [dde-store](https://github.com/dekzi/dde-store) 的系统通知发送方式

GitHub 大佬 [xmuli](https://github.com/xmuli) 的 [Qt 项目(Cmake)设置国际化支持](https://ifmet.cn/posts/9644ed82/) 方法

论坛大佬 chanforever 的 [DDESwitchCard](https://github.com/mywhat/DDESwitchCard) 插件        https://bbs.deepin.org/zh/post/197280

论坛大佬 jfy_99 的显卡切换脚本     https://bbs.deepin.org/zh/post/192750

论坛大佬 risez 的 nvidia-prime 方案        https://bbs.deepin.org/zh/post/191741

论坛大佬 q77190858 的 [dde-sys-monitor-plugin](https://github.com/q77190858/dde-sys-monitor-plugin) 插件        https://bbs.deepin.org/zh/post/179425

论坛大佬 shenmo，lenke，mmlmonkey，xuey 等提供的修改建议       https://bbs.deepin.org/zh/post/197367

码云组织 [开源应用](https://gitee.com/deepin-opensource) 提供的 UOS 打包规范和方法
