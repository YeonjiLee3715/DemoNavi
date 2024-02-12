cmake_minimum_required(VERSION 3.16)

project(BaseComponents VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(BASECOMPONENTS_INCLUDES
    src/defines/baseComponentsDefs.h
    src/QBaseView.h
    src/handlers/QBaseEventHandler.h
    src/handlers/QWindowEventHandler.h
    src/handlers/QButtonEventHandler.h
    src/handlers/QComboBoxEventHandler.h
    src/handlers/QListEventHandler.h
    src/handlers/QTextEditEventHandler.h
    src/handlers/QViewEventHandler.h
)

include_directories(
    src
    src/handlers
    src/defines
    src/logger
)

set(SOURCE_FILES
    src/QBaseView.cpp
    src/logger/CLogger.cpp
# modules/viewModule/handlers
    src/handlers/QBaseEventHandler.cpp
    src/handlers/QButtonEventHandler.cpp
    src/handlers/QComboBoxEventHandler.cpp
    src/handlers/QListEventHandler.cpp
    src/handlers/QTextEditEventHandler.cpp
    src/handlers/QViewEventHandler.cpp
    src/handlers/QWindowEventHandler.cpp
)

set(HEADERS_FILES
    src/defines/cmnDef.h
    src/logger/CLogger.h
    ${BASECOMPONENTS_INCLUDES}
)

qt_add_library(BaseComponents STATIC
    ${SOURCE_FILES}
    ${HEADERS_FILES}
)
qt_add_qml_module(BaseComponents
    URI com.custom.basecomponents
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml/basecomponents"
    QML_FILES
        res/BaseWindow.qml
        res/BaseView.qml
        res/BaseButton.qml
        res/BaseTextEdit.qml
        res/BaseCombobox.qml
        res/BaseListView.qml
        res/BaseTreeView.qml
    SOURCES
        src/defines/baseComponentsDefs.h
)

set_target_properties(BaseComponents PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(BaseComponents PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(BaseComponents PRIVATE
    Qt6::Quick
)

file(COPY ${BASECOMPONENTS_INCLUDES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(BaseComponents INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
