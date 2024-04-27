cmake_minimum_required(VERSION 3.16)

project(TestTaskGis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 Quick3D REQUIRED)

qt_add_executable(TestTaskGis
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

qt_add_qml_module(TestTaskGis
    URI test
    VERSION 1.0
    QML_FILES main.qml
    RESOURCES
    QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(TestTaskGis PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTestTaskGis
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(TestTaskGis
    PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Quick3D)

include(GNUInstallDirs)
install(TARGETS TestTaskGis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
