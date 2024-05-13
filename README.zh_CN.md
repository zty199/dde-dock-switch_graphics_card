# dde-dock-graphics-plugin (forked from [mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard/))

[![英文](https://img.shields.io/badge/语言-英文-blue.svg)](https://github.com/zty199/dde-dock-switch_graphics_card/blob/master/README.md)
[![中文](https://img.shields.io/badge/语言-中文-red.svg)](https://gitee.com/deepin-opensource/switch-graphics-card/blob/master/README.zh_CN.md)

原贴地址：[切换显卡插件](https://bbs.deepin.org/zh/post/197280)

## 介绍

切换显卡插件原作者为 [chanforever](https://bbs.deepin.org.cn/user/165937) 大佬，在 dde-dock 中为用户提供快速切换显卡的入口。

目前仅支持 **Intel 核显 + NVIDIA 独显**，且不支持独显直连的笔记本。
> 部分屏蔽核显，或支持 DDG 显卡直连技术的笔记本无需使用该插件。

* **AMD 核显 + NVIDIA 独显** 的笔记本理论上也支持（？）

  如果切换后造成 xserver 无法启动，可在 tty2 中执行 `/opt/apps/dde-dock-graphics-plugin/files/bin/Rescue.sh` 还原插件修改。

## 依赖

### 构建依赖

* cmake
* debhelper
* qtchooser
* qt6-base-dev
* qt6-tools-dev
* qt6-svg-dev
* libdtk6core-dev
* libdtk6widget-dev
* dde-dock-dev

使用以下命令安装所需依赖:
```bash
$ sudo apt build-dep .
```

### 运行依赖

* libqt6svg6
* dde-control-center
* dde-shell (>= 0.0.6)
* dde-application
* mesa-utils
* pkexec
* zenity

## 安装

确保你已经安装全部依赖。

使用以下命令构建二进制软件包：
```bash
$ dpkg-buildpackage -Zxz -rfakeroot -uc -us -nc -b -j$(nproc)
```

> 二进制软件包将生成在上级目录。

## 感谢

* [mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard) -> [切换显卡插件](https://bbs.deepin.org/zh/post/197280)
* [deepin-espanol/dde-dock-graphics-plugin](https://github.com/deepin-espanol/dde-dock-graphics-plugin)
* [Dziban-dev/dde-appknitter](https://github.com/Dziban-dev/dde-appknitter)
* [q77190858/dde-sys-monitor-plugin](https://github.com/q77190858/dde-sys-monitor-plugin)
* [Qt 项目(Cmake)设置国际化支持](https://ifmet.cn/posts/9644ed82/)

---

* [论坛大佬 jfy_99 的显卡切换脚本](https://bbs.deepin.org/zh/post/192750)
* [论坛大佬 risez 的 nvidia-prime 方案](https://bbs.deepin.org/zh/post/191741)
* [论坛大佬 shenmo，lenke，mmlmonkey，xuey 等提供的修改建议](https://bbs.deepin.org/zh/post/197367)

## 参考

* [linuxdeepin/dde-dock](https://github.com/linuxdeepin/dde-dock)
* [linuxdeepin/dde-shell](https://github.com/linuxdeepin/dde-shell)
* [linuxdeepin/dde-file-manager](https://github.com/linuxdeepin/dde-file-manager)
* [linuxdeepin/dtkcore](https://github.com/linuxdeepin/dtkcore) / [linuxdeepin/dtk6core](https://github.com/linuxdeepin/dtk6core)
* [linuxdeepin/dde-application-manager](https://github.com/linuxdeepin/dde-application-manager) 
