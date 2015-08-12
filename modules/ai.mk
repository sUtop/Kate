## -*- Makefile -*-
##
## Пользователь: utop
## Время: 10.08.2015 3:02:44
## Makefile created by Oracle Solaris Studio.
##

LFLAGS += -Wall -Ofast -std=c++11 -I./ -pipe -O2 -lpthread $(INCLUDES) $(DEBUG) # -D_REENTRANT 
CFLAGS = -c $(LFLAGS)

bin/ai: bin/ai
	echo "building ai module"
	mkdir -p obj
	mkdir -p bin
	$(CXX) $(LFLAGS) -pthread  modules/ai/ai.cpp -o bin/ai

.PHONY : clean
clean:
	rm -rf bin/ai obj

