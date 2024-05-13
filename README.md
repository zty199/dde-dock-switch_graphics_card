# dde-dock-graphics-plugin (forked from [mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard/))

[![en-US](https://img.shields.io/badge/lang-en--US-blue.svg)](https://github.com/zty199/dde-dock-switch_graphics_card/blob/master/README.md)
[![zh-Hans](https://img.shields.io/badge/lang-zh--Hans-red.svg)](https://gitee.com/deepin-opensource/switch-graphics-card/blob/master/README.zh_CN.md)

Original BBS Post：[切换显卡插件](https://bbs.deepin.org/zh/post/197280)

## Introduction

This dde-dock plugin is originally written by chanforever, designed for quick access from dde-dock to switch between different graphics cards to run X11 server.

For now only support **Intel IGPU + NVIDIA DGPU** laptops with internal display connected to IGPU.
> Laptops with internal display connected to DGPU, or those with DDG(Dual-Direct GFX) technology won't need this plugin.

* **AMD APU + NVIDIA DGPU** laptops are theortically supported(?)

  Ofcourse it only shows `Intel graphics` in dde-dock, but since using `modesetting` module in xorg.conf, APU should work......

  If you switch to `Intel graphics` and xserver failed to start, you can run `/opt/apps/dde-dock-graphics-plugin/files/bin/Rescue.sh` in tty2 to revert modifications in `/etc/X11/xorg.conf` and `/etc/lightdm/lightdm.conf`.

## Dependencies

### build-deps

* cmake
* debhelper
* qtchooser
* qt6-base-dev
* qt6-tools-dev
* qt6-svg-dev
* libdtk6core-dev
* libdtk6widget-dev
* dde-dock-dev

Use the following command to install required dependencies:
```bash
$ sudo apt build-dep .
```

### runtime-deps

* libqt6svg6
* dde-control-center
* dde-shell (>= 0.0.6)
* dde-application
* mesa-utils
* pkexec
* zenity

## Installation
Make sure you have installed all dependencies.

Use the following command to build binary package:
```bash
$ dpkg-buildpackage -Zxz -rfakeroot -uc -us -nc -b -j$(nproc)
```

> The binary package will be generated in parent directory.

## Credits

* [mywhat/DDESwitchCard](https://github.com/mywhat/DDESwitchCard) -> [切换显卡插件](https://bbs.deepin.org/zh/post/197280)
* [deepin-espanol/dde-dock-graphics-plugin](https://github.com/deepin-espanol/dde-dock-graphics-plugin)
* [Dziban-dev/dde-appknitter](https://github.com/Dziban-dev/dde-appknitter)
* [q77190858/dde-sys-monitor-plugin](https://github.com/q77190858/dde-sys-monitor-plugin)
* [Qt 项目(Cmake)设置国际化支持](https://ifmet.cn/posts/9644ed82/)

---

* [shell scripts to switch graphics card from jfy_99](https://bbs.deepin.org/zh/post/192750)
* [a possible way to use nvidia-prime from risez](https://bbs.deepin.org/zh/post/191741)
* [modification suggestions from shenmo, lenke, mmlmonkey, xuey, etc.](https://bbs.deepin.org/zh/post/197367)

## References

* [linuxdeepin/dde-dock](https://github.com/linuxdeepin/dde-dock)
* [linuxdeepin/dde-shell](https://github.com/linuxdeepin/dde-shell)
* [linuxdeepin/dde-file-manager](https://github.com/linuxdeepin/dde-file-manager)
* [linuxdeepin/dtkcore](https://github.com/linuxdeepin/dtkcore) / [linuxdeepin/dtk6core](https://github.com/linuxdeepin/dtk6core)
* [linuxdeepin/dde-application-manager](https://github.com/linuxdeepin/dde-application-manager) 
