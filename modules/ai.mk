## -*- Makefile -*-
##
## Пользователь: utop
## Время: 10.08.2015 3:02:44
## Makefile created by Oracle Solaris Studio.
##

LFLAGS_AI = -Wall -Ofast -std=c++11 -I./ -pipe -lpthread $(INCLUDES) $(DEBUG) # -D_REENTRANT 

bin/ai: bin/ai
	echo "building ai module"
	mkdir -p obj
	mkdir -p bin
	$(CXX) $(LFLAGS_AI) -pthread  modules/ai/ai.cpp -o bin/ai

.PHONY : clean
clean:
	rm -rf bin/ai obj

