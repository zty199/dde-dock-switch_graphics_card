# Have to disable cleaning for this folder because cmake deletes .ts files upon clean
# Not sure what else wont clean up / dirty workaround of Qt bug
# @ref https://bugreports.qt.io/browse/QTBUG-41736
# @ref https://stackoverflow.com/a/24245615/1917249
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM TRUE)

# By default, the generated .qm files are embedded in a Qt resource
# that will be linked into the targets passed with TARGETS.
# The files in the resource are accessible under the resource prefix "/i18n".
# This feature needs cmake Qt6Core module.
# @ref https://doc.qt.io/qt-6.8/qtlinguist-cmake-qt-add-translations.html#embedding-generated-qm-files-in-resources
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES en es zh_CN)

# Update ts files and release qm files only in Release build
if (NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
    include(${CMAKE_SOURCE_DIR}/src/src.cmake)
    qt_add_translations(${PROJECT_NAME}
                        SOURCES ${HEADERS} ${SOURCES}
                        LUPDATE_OPTIONS -no-obsolete)
    add_dependencies(${PROJECT_NAME} update_translations)
endif ()
