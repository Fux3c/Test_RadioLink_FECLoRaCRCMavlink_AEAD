cmake_minimum_required(VERSION 3.16)

project(NRS-Groundstation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#Legger til Qt Charts i CMake-prosjektet:
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)


find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
target_link_libraries(ditt_prosjektnavn
    Qt5::Widgets
    Qt5::Charts
)


qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appNRS-Groundstation
    main.cpp
)

qt_add_qml_module(appNRS-Groundstation
    URI NRS-Groundstation
    VERSION 1.0
    QML_FILES Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNRS-Groundstation PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNRS-Groundstation
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNRS-Groundstation
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appNRS-Groundstation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
