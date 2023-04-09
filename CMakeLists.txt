cmake_minimum_required(VERSION 3.16)

project(XcodeReleases VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Quick QuickControls2 Network)

qt_standard_project_setup()

qt_add_executable(appXcodeReleases
    main.cpp
    xcodedata.hpp
    xcodedata.cpp
)

qt_add_qml_module(appXcodeReleases
    URI XcodeReleases
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appXcodeReleases PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER app.genyleap.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

target_link_libraries(appXcodeReleases
    PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2 Qt6::Network
)

install(TARGETS appXcodeReleases
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
