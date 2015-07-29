
#LIBS += -L./obj/  -lphz -Wl,-rpath,./obj/
OBJS += obj/phz.o


#libphz.a:
#phz.o: #phz/phz.cpp
#all:
#libphz.a:
obj/phz.o:
	echo "building Phz module"
	mkdir -p obj
	$(CC) $(CFLAGS) modules/phz/phz.cpp -o obj/phz.o
#	ar cr obj/libphz.a modules/phz/phz.cpp lib.h
