#!/bin/sh

cd $PWD

# 编译
echo "开始编译..."

mkdir build && cd build
cmake ../src
make
cd ..

echo "编译完成"

# 打包
echo "构建软件包..."

mkdir -p ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/bin/
mkdir -p ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/plugins/
mkdir -p ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/share/icons/
mkdir -p ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/share/oem-menuextensions/

cp ./build/libswitch_graphics_card.so ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/plugins
cp ./scripts/* ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/bin/
cp ./icons/* ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/share/icons/
cp ./oem-menuextensions/prime-run.desktop ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/share/oem-menuextensions/

find ./deb_uos/opt -type f -print0 | xargs -0 md5sum > ./deb_uos/DEBIAN/md5sums && sed -i "s#./deb_uos/opt#/opt#" ./deb_uos/DEBIAN/md5sums

echo "----------包信息----------"

cat ./deb_uos/DEBIAN/control

echo "-------------------------"

fakeroot dpkg -b ./deb_uos ./dde-dock-graphics-plugin_amd64.deb

echo "构建完成，软件包位于当前目录"

# 清除模板中的文件
echo "清除文件..."

rm -rf ./deb_uos/opt/apps/com.deepin.dde-dock-graphics-plugin/files/*

# rm -rf ./build
