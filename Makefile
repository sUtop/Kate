# подключение модулей
#include modules/inout.mk

PROG = bin/Kate
OBJS = obj/main.o obj/dispatcher.o # msg.o bd.o phz.o
#OBJS = *.o *.lib   inout.o 
#OBJS_LINK = *.o *.lib

CC=g++
CXX = $(CC)
DEBUG=-g
INCLUDES += -I./
LFLAGS += -Wall -std=c++11 -pipe -O2 -lpthread $(INCLUDES) $(DEBUG) # -D_REENTRANT 
CFLAGS = -c $(LFLAGS)
#  -lm -lz 
LIBS +=
LIBNAME += 


#include modules/*.mk

all: modules ${PROG}

${PROG}: $(OBJS)
	echo $(LIBS)
	mkdir -p bin
	$(CXX) $(LFLAGS) -pthread  -o $(PROG) $(OBJS) $(LIBS)
	cp Kate.conf bin/
#	mv ${PROG} bin/${PROG}
#	mkdir -p bin/obj
#	cp -f $(LIBNAME) bin/obj/
#Kate: main.o dispatcher.o msg.o bd.o inp.o out.o phz.o
#	$(CC) $(LFLAGS) main.o dispatcher.o msg.o bd.o inp.o out.o phz.o -o Kate


obj/main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o obj/main.o

obj/dispatcher.o: dispatcher.cpp
	$(CC) $(CFLAGS) dispatcher.cpp -o obj/dispatcher.o


#msg.o: modules/msg/msg.cpp
#	$(CC) $(CFLAGS) modules/msg/msg.cpp

#bd.o: modules/bd/bd.cpp
#	$(CC) $(CFLAGS) modules/bd/bd.cpp

#phz.o: modules/phz/phz.cpp
#	$(CC) $(CFLAGS) modules/phz/phz.cpp

modules: obj/msg.o obj/bd.o obj/libinout.a obj/phz.o

obj/msg.o:
include modules/msg.mk

obj/bd.o:
include modules/bd.mk
#	make -f  modules/bd.mk

obj/libinout.a: 
include modules/inout.mk
#	make -f modules/inout.mk

obj/phz.o:
include modules/phz.mk
#	make -f modules/phz.mk

.PHONY : clean
clean:
	rm -rf obj/ bin/ *.gnu #*.o *.app *.dylib *.a lib*.so* .*log Kate  *.gnu 