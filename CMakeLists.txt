cmake_minimum_required(VERSION 3.16)

project(ComplexityTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Qt6PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6PrintSupport REQUIRED)



add_executable(ComplexityTest
            main.cpp
            mainwindow.h mainwindow.cpp mainwindow.ui
            qcustomplot.cpp qcustomplot.h
            plotwindow.h plotwindow.cpp plotwindow.ui
)

target_link_libraries(ComplexityTest PRIVATE Qt6::Widgets
                        Qt6::PrintSupport)
