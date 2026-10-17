cmake_minimum_required(VERSION 3.21)

project(QtCicdDemo
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(todoapp
    src/main.cpp
)

set_source_files_properties(qml/Main.qml PROPERTIES QT_RESOURCE_ALIAS Main.qml)
set_source_files_properties(qml/TodoDelegate.qml PROPERTIES QT_RESOURCE_ALIAS TodoDelegate.qml)

qt_add_qml_module(todoapp
    URI TodoApp
    QML_FILES
        qml/Main.qml
        qml/TodoDelegate.qml
    SOURCES
        src/todomodel.h
        src/todomodel.cpp
)

target_include_directories(todoapp PRIVATE src)

target_link_libraries(todoapp PRIVATE Qt6::Quick)

set_target_properties(todoapp PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
