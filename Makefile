
CC=g++
DEBUG=-g
LFLAGS = -Wall -std=c++14 -lpthread $(DEBUG) # -D_REENTRANT 
CFLAGS = -c $(LFLAGS)

all: Kate

Kate: main.o dispatcher.o msg.o bd.o inp.o out.o phz.o
	$(CC) $(LFLAGS) main.o dispatcher.o msg.o bd.o inp.o out.o phz.o -o Kate

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

dispatcher.o: dispatcher.cpp
	$(CC) $(CFLAGS) -c dispatcher.cpp

msg.o: modules/msg/msg.cpp
	$(CC) $(CFLAGS) -c modules/msg/msg.cpp

bd.o: modules/bd/bd.cpp
	$(CC) $(CFLAGS) -c modules/bd/bd.cpp

inp.o: modules/inp/inp.cpp
	$(CC) $(CFLAGS) -c modules/inp/inp.cpp

out.o: modules/out/out.cpp
	$(CC) $(CFLAGS) -c modules/out/out.cpp

phz.o: modules/phz/phz.cpp
	$(CC) $(CFLAGS) -c modules/phz/phz.cpp

clean:
	rm -rf *.o Kate
