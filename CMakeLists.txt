cmake_minimum_required(VERSION 3.16)
project(kr)

set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt/5.14.2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Quick QuickControls2 Qml Core  REQUIRED)

file(GLOB_RECURSE RESOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/*.qrc)

message(${RESOURCES})

set(CMAKE_CXX_STANDARD 20)

add_executable(kr main.cpp ${RESOURCES})

target_include_directories(kr PUBLIC ${QtQml_INCLUDE_DIRS} ${QtQuick_INCLUDE_DIRS} ${QtCore_INCLUDE_DIRS})
target_include_directories(kr PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_definitions(${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
target_link_libraries(kr Qt5::Quick Qt5::QuickControls2 Qt5::Qml Qt5::Core)