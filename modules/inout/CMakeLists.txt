
cmake_minimum_required(VERSION 3.0.0)
project(inout)
# Настройки подключения Qt

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(OpenGL)
#find_package(Qt5Core REQUIRED)

set(QMAKE_CXXFLAGS "${QMAKE_CXXFLAGS} -std=c++11 -v -fPIC")


# Настройки модуля
set( HEADERS
    ${ROOT_DIR}/dispatcher/lib.h
    inout.h
    keyboard.h
    sender.h
    widget.h)

set( SOURCES
    ${ROOT_DIR}/dispatcher/lib.cpp
    inout.cpp
    keyboard.cpp
    sender.cpp
    widget.cpp)

add_library(inout SHARED
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})
#

qt5_use_modules(inout Gui Core OpenGL)
#Gl  QOpengl

target_link_libraries(inout 
    ${QT_LIBRARIES} 
    ${OPENGL_LIBRARIES})

message("       Module inout added ?")
