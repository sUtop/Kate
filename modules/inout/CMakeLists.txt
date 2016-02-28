
cmake_minimum_required(VERSION 3.0.0)
project(inout)
# Настройки подключения Qt

if(${U_PLATFORM} MATCHES "MAC")
# !Choose your correct qt path
    set(QTMAIN_PATH "~/Qt/")

    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}${QTMAIN_PATH}")

#find_library( OPENGL_LIBRARY OpenGL )
#find_package(Qt5PrintSupport)
endif (${U_PLATFORM} MATCHES "MAC")

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(OpenGL)

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
#    ${OPENGL_LIBRARY}
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})
#

#if(${U_PLATFORM} MATCHES "LINUX")

qt5_use_modules(inout PrintSupport Gui Core OpenGL)

#elseif (${U_PLATFORM} MATCHES "MAC")

#qt5_use_modules(inout PrintSupport Gui Core OpenGL)

#endif (${U_PLATFORM} MATCHES "LINUX")

#Gl  QOpengl

target_link_libraries(inout
#    ${OPENGL_LIBRARY}
    ${QT_LIBRARIES} 
    ${OPENGL_LIBRARIES})

message("       Module inout added ?")
