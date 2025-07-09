cmake_minimum_required(VERSION 3.16)
project(MNote LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(MNote
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/font.qrc          
)

target_link_libraries(MNote PRIVATE Qt6::Widgets)
