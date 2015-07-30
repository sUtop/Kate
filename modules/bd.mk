
#LIBS += -L./obj/  -lphz -Wl,-rpath,./obj/
OBJS += obj/bd.o


#libbd.a: #bd/bd.cpp
#all:
#libbd.a:
obj/bd.o:
	echo "building bd module"
	mkdir -p obj
	$(CC) $(CFLAGS) modules/bd/bd.cpp -o obj/bd.o
#	$(CC) $(CFLAGS) modules/msg/msg.cpp
#	ar cr obj/libbd.a modules/bd/bd.cpp lib.h


#	$(QMAKE) modules/inout.pro
#	make -f inout.gnu
#	cp /usr/local/Qt-5.5.0/lib/QtOpenGL.framework/Versions/Current/QtOpenGL ./

