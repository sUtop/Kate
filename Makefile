# подключение модулей
#include modules/inout.mk

PROG = Kate
OBJS = main.o dispatcher.o msg.o bd.o phz.o
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

all: libinout.a ${PROG}

${PROG}: $(OBJS)
	echo $(LIBS)
	$(CXX) $(LFLAGS) -pthread  -o $(PROG) $(OBJS) $(LIBS)
#Kate: main.o dispatcher.o msg.o bd.o inp.o out.o phz.o
#	$(CC) $(LFLAGS) main.o dispatcher.o msg.o bd.o inp.o out.o phz.o -o Kate


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

dispatcher.o: dispatcher.cpp
	$(CC) $(CFLAGS) dispatcher.cpp

msg.o: modules/msg/msg.cpp
	$(CC) $(CFLAGS) modules/msg/msg.cpp

bd.o: modules/bd/bd.cpp
	$(CC) $(CFLAGS) modules/bd/bd.cpp

libinout.a: 
include modules/inout.mk

phz.o: modules/phz/phz.cpp
	$(CC) $(CFLAGS) modules/phz/phz.cpp

clean:
	rm -rf *.o *.gnu *.app *.dylib *.a lib*.so* .*log Kate 
