cmake_minimum_required(VERSION 3.11)

project(dde-dock-graphics-plugin)

if (NOT DEFINED VERSION)
    set(VERSION 1.6.0)
endif ()

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 启用 qt moc 的支持
set(CMAKE_AUTOMOC ON)
# 启用 qrc 资源文件的支持
set(CMAKE_AUTOUIC ON)

# 使用 cmake 的 file 命令，递归查找项目目录下所有脚本文件
file(GLOB SCRIPTS "${CMAKE_SOURCE_DIR}/scripts/*.sh")

add_subdirectory(src)

# 设置安装路径的前缀(默认为 "/usr/local")
set(CMAKE_INSTALL_PREFIX "/opt")

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
install(FILES "${CMAKE_SOURCE_DIR}/gschema/com.deepin.dde.dock.module.switch-graphics-card.gschema.xml" DESTINATION apps/${PROJECT_NAME}/entries/glib-2.0/schemas)
install(FILES "${CMAKE_SOURCE_DIR}/oem-menuextensions/prime-run.desktop" DESTINATION apps/${PROJECT_NAME}/files/share/oem-menuextensions)
install(FILES "${CMAKE_SOURCE_DIR}/pkexec/com.deepin.pkexec.dde-dock-graphics-plugin.policy" DESTINATION apps/${PROJECT_NAME}/entries/polkit/actions)
install(FILES ${SCRIPTS} DESTINATION apps/${PROJECT_NAME}/files/bin)
