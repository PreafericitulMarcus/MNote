cmake_minimum_required(VERSION 3.28)
project(MNote LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MNote main.cpp mainwindow.cpp)
target_link_libraries(MNote Qt6::Widgets)
