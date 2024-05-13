include_directories(${CMAKE_SOURCE_DIR}/include)

# @ref https://cmake.org/cmake/help/v3.12/command/file.html#glob-recurse
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

qt6_add_resources(QRC_FILE ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
