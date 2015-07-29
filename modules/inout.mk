#QMAKE         = /Users/utop/Qt5.4.0/5.4/clang_64/bin/qmake
#QMAKE = /Users/utop/Qt5.4.0/5.4/Src/qtbase/qmake
QMAKE = qmake
LIBS += -L./bin  -linout -Wl,-rpath,./bin -Wl,-rpath,/usr/local/Qt-5.5.0/lib/
#-L./usr/local/Qt-5.5.0/lib/QtOpenGL.la
#/usr/local/Qt-5.5.0/lib/QtOpenGL.framework/QtOpenGL# -framework QtOpenGL
#LFLAGS += -lqtgl
#INCLUDEPATH += /opt/X11/include/ /usr/local/Qt-5.5.0/lib/
#.PHONY : libinout
#libinout.a:

LIBNAME += obj/libinout*

obj/libinout.a: 
	echo "building InOut module"
	$(QMAKE) modules/inout.pro
	pwd
	make -f inout.gnu
#	cp /usr/local/Qt-5.5.0/lib/QtOpenGL.framework/Versions/Current/QtOpenGL ./

#	$(QMAKE) inout.pro
#	@make
	
#clean:
#	rm -rf Makefile *.o

#QT       += gui core opengl

#TARGET   = inout.o
#TEMPLATE = app

#SOURCES += inout/inout.cpp 

#HEADERS  += inout/inout.h

#inout.o: 
