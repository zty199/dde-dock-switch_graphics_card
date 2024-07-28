find_package(Qt5 COMPONENTS Core Widgets DBus Svg REQUIRED)
find_package(Dtk COMPONENTS Core Widget REQUIRED)
find_package(DdeTrayLoader REQUIRED)

include(src.cmake)

add_library(${PROJECT_NAME} MODULE ${HEADERS} ${SOURCES} ${QRC_FILE})

target_include_directories(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::DBus
    Qt5::Svg
    Dtk::Core
    Dtk::Widget
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::DBus
    Qt5::Svg
    Dtk::Core
    Dtk::Widget
)

set(PLUGIN_NAME switch-graphics-card)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PLUGIN_NAME})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/plugins)

install(FILES ${CMAKE_SOURCE_DIR}/resources/dde-dock-graphics-plugin.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/entries/applications)
#install(FILES ${CMAKE_SOURCE_DIR}/resources/gschema/com.deepin.dde.dock.module.switch-graphics-card.gschema.xml DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/entries/glib-2.0/schemas)
install(FILES ${CMAKE_SOURCE_DIR}/resources/pkexec/com.deepin.pkexec.dde-dock-graphics-plugin.policy DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/entries/polkit/actions)
install(FILES ${CMAKE_SOURCE_DIR}/resources/oem-menuextensions/prime-run.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/share/oem-menuextensions)
install(FILES ${CMAKE_SOURCE_DIR}/resources/icons/${PLUGIN_NAME}.svg DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/share/icons)

configure_file(${CMAKE_SOURCE_DIR}/resources/info.in ${CMAKE_SOURCE_DIR}/resources/info @ONLY)
install(FILES ${CMAKE_SOURCE_DIR}/resources/info DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME})

file(GLOB SCRIPTS ${CMAKE_SOURCE_DIR}/resources/scripts/*.sh)
install(FILES ${SCRIPTS} DESTINATION ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)

# create symlinks
# @ref https://github.com/deepin-espanol/dde-dock-graphics-plugin/blob/master/src/CMakeLists.txt
file(CREATE_LINK ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/plugins/lib${PLUGIN_NAME}.so ${CMAKE_CURRENT_BINARY_DIR}/lib${PLUGIN_NAME}.link SYMBOLIC)
file(CREATE_LINK ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/bin/prime-run.sh ${CMAKE_CURRENT_BINARY_DIR}/prime-run.link SYMBOLIC)
file(CREATE_LINK ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/share/oem-menuextensions/prime-run.desktop ${CMAKE_CURRENT_BINARY_DIR}/prime-run-desktop.link SYMBOLIC)
file(CREATE_LINK ${CMAKE_INSTALL_PREFIX}/apps/${PROJECT_NAME}/files/share/icons/${PLUGIN_NAME}.svg ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_NAME}-svg.link SYMBOLIC)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${PLUGIN_NAME}.link DESTINATION /usr/lib/dde-dock/plugins RENAME lib${PLUGIN_NAME}.so)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/prime-run.link DESTINATION /usr/bin RENAME prime-run)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/prime-run-desktop.link DESTINATION /usr/share/deepin/dde-file-manager/oem-menuextensions RENAME prime-run.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_NAME}-svg.link DESTINATION /usr/share/dde-dock/icons/dcc-setting RENAME ${PLUGIN_NAME}.svg)
