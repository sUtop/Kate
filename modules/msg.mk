
#CC=g++
#CXX = $(CC)
#DEBUG=-g
#INCLUDES += -I./
#LFLAGS += -Wall -std=c++11 -pipe -O2 -lpthread $(INCLUDES) $(DEBUG) # -D_REENTRANT 
#CFLAGS = -c $(LFLAGS)
#LIBS += -L./obj/  -lmsg -Wl,-rpath,./obj/
OBJS += obj/msg.o

#obj/libmsg.a: #msg/msg.cpp
#all:
obj/msg.o:
	echo "building msg module"
	mkdir -p obj
	$(CC) $(CFLAGS) modules/msg/msg.cpp -o obj/msg.o
#	ar cr obj/libmsg.a modules/msg/msg.cpp lib.h

