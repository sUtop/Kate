
PROG = Kate
OBJS = main.o dispatcher.o msg.o bd.o inout.o phz.o
CC=g++
CXX = $(CC)
DEBUG=-g
INCLUDES = -I ./
LFLAGS = -Wall -std=c++14 -lpthread $(INCLUDES) $(DEBUG) # -D_REENTRANT 
CFLAGS = -c $(LFLAGS)

all: ${PROG}

${PROG}: $(OBJS)
	$(CXX) $(INCLUDES) -o $(PROG) $(OBJS) $(LIBS)
#Kate: main.o dispatcher.o msg.o bd.o inp.o out.o phz.o
#	$(CC) $(LFLAGS) main.o dispatcher.o msg.o bd.o inp.o out.o phz.o -o Kate

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

dispatcher.o: dispatcher.cpp
	$(CC) $(CFLAGS) -c dispatcher.cpp

msg.o: modules/msg/msg.cpp
	$(CC) $(CFLAGS) -c modules/msg/msg.cpp

bd.o: modules/bd/bd.cpp
	$(CC) $(CFLAGS) -c modules/bd/bd.cpp

inout.o: modules/inout/inout.cpp
	$(CC) $(CFLAGS) -c modules/inout/inout.cpp

phz.o: modules/phz/phz.cpp
	$(CC) $(CFLAGS) -c modules/phz/phz.cpp

clean:
	rm -rf *.o Kate
