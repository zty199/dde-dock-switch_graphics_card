cmake_minimum_required(VERSION 3.19)

project(dde-dock-graphics-plugin VERSION 2.1.0 LANGUAGES CXX)
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")

if (NOT DEFINED VERSION)
    set(VERSION ${PROJECT_VERSION})
endif ()
add_compile_definitions(VERSION="${VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOMOC_COMPILER_PREDEFINES ON)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

include(GNUInstallDirs)

# Force use Qt6
set(QT_VERSION_MAJOR 6)
set(DTK_VERSION_MAJOR 6)

add_subdirectory(src)
add_subdirectory(translations)
