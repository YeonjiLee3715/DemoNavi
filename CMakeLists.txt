cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(DemoNaviApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Network
    Quick
    Positioning
    Location
    LinguistTools
)

set(CMAKE_CXX_STANDARD 17)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

add_subdirectory("BaseComponents")

include_directories(
    src
    src/commonLibs
    src/defs
    src/modules
    src/modules/viewModule
    src/modules/viewModule/views
)

set(SOURCE_FILES
    src/main.cpp
    src/DemoNavi.cpp
# commonLibs
    src/commonLibs/QBaseModule.cpp
    src/commonLibs/QModuleManager.cpp
    src/commonLibs/CLogger.cpp
    src/commonLibs/CStrManager.cpp
# modules
    src/modules/ModuleEnum.cpp
    src/modules/QModuleFactory.cpp
# modules/viewModule
    src/modules/viewModule/ViewControlModule.cpp
    src/modules/viewModule/views/NaviHomeView.cpp
)

set(HEADERS_FILES
    src/DemoNavi.h
# commonLibs
    src/commonLibs/commonLibsDef.h
    src/commonLibs/QBaseModule.h
    src/commonLibs/QModuleManager.h
    src/commonLibs/CLogger.h
    src/commonLibs/CStrManager.h
# defs
    src/defs/cmnDefs.h
    src/defs/viewDefs.h
# modules
    src/modules/QModuleFactory.h
    src/modules/ModuleEnum.h
# modules/viewModule
    src/modules/viewModule/ViewControlModule.h
    src/modules/viewModule/views/NaviHomeView.h
)

qt_add_executable(DemoNaviApp
    ${SOURCE_FILES}
    ${HEADERS_FILES}
)

# Resources:
set(RES_QML_FILES
#components
    "res/qml/Components/FlatButton.qml"
    "res/qml/Components/IconTextEdit.qml"
    "res/qml/Components/ListView.qml"
    "res/qml/Components/TabButton.qml"
#Views
    "res/qml/Views/NaviHomeView.qml"
)

qt_add_resources(DemoNaviApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(DemoNaviApp PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Location
    Qt::Network
    Qt::Positioning
    Qt::Qml
    Qt::Quick
    BaseComponents
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

qt6_add_qml_module(${CMAKE_PROJECT_NAME}
    URI Main
    VERSION 1.0
    RESOURCE_PREFIX "/"
    NO_PLUGIN
    QML_FILES
        ${RES_QML_FILES}
        "res/qml/main.qml"
    RESOURCES
        "res/qml/Components/qmldir"
        "res/qml/Views/qmldir"
        "qtquickcontrols2.conf"
        "res/img/marker.png"
        "res/img/marker_blue.png"
        "res/img/aim.png"
        "res/img/search.png"
)

add_subdirectory(content)
add_subdirectory(imports)

target_link_libraries(DemoNaviApp PRIVATE
    contentplugin
    DemoNaviplugin
    BaseComponentsplugin
)

# set language files
set(DEMONAVI_TS_FILES
    DemoNavi_en_US.ts
)

qt_add_lupdate(DemoNaviApp TS_FILES ${DEMONAVI_TS_FILES})
qt_add_lrelease(DemoNaviApp
    TS_FILES ${DEMONAVI_TS_FILES}
    QM_FILES_OUTPUT_VARIABLE qm_files
)
qt_add_resources(DemoNaviApp "translations"
    PREFIX "/i18n"
    BASE "${CMAKE_CURRENT_BINARY_DIR}"
    FILES "${qm_files}"
)
# end language file setting

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS DemoNaviApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
