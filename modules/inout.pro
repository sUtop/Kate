#QT       += gui core opengl 
#CONFIG += c++14 opengl pthread exceptions qt
#QMAKE_CXXFLAGS += -std=c++14 -v -lpthread -lGL 
#QMAKE_CFLAGS_THREAD = -pthread -D_THREAD_SAFE

QT       += gui core opengl  # pthread
CONFIG += c++11 -fPIC
QMAKE_CXXFLAGS += -std=c++11 -v -fPIC

LIBS += -lpthread 

TARGET   = inout
DESTDIR  = ../
TEMPLATE = lib


SOURCES  += inout/inout.cpp inout/widget.cpp inout/keyboard.cpp
HEADERS  += inout/inout.h inout/widget.h inout/keyboard.h


INCLUDEPATH += /opt/X11/include/ ./ ../ /usr/local/Qt-5.5.0/lib/ \
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/ \
/usr/local/Qt-5.5.0/lib/QtGui.framework/Versions/Current/Headers/ \
/usr/local/Qt-5.5.0/lib/QtWidgets.framework/Versions/Current/Headers/ \
/usr/local/Qt-5.5.0/lib/QtOpenGL.framework/Versions/Current/Headers/
# /usr/local/Qt-5.5.0/lib/QtOpenGL.framework/Versions/Current/QtOpenGL \

MAKEFILE = inout.gnu

