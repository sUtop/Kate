// Модуль управления потоками

#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include <list>
#include <iostream>
#include <string>
#include "lib.h"

// Модуль диспетчера не обязан знать где и какие модули лежат
// однако как это сделать пока непонятно. Поэтому
// временное решение - прямое включение модулей.
#include "../modules/msg/msg.h"
extern MessageDispeather *messager;
#include "../modules/bd/bd.h"
extern DataBase *database;
#include "../modules/inout/inout.h"
extern InputOutput *inputoutput;
#include "../modules/phz/phz.h"
extern Physics *physics;

//char** mainargv;
//int mainargc;

typedef void (*PFunction) ();
typedef std::list<std::thread*> thredList;
typedef std::map<std::string,thredList> mapListsThreads;
typedef std::list<std::string, std::allocator<std::string> > inputString;
typedef std::map<std::string,PFunction> mapListPFunction;
typedef std::map<std::string,module*> mapListPModule;

class dispatcher{
    //	Thread* Th;
    mapListsThreads threads;     // Список потоков
    mapListPFunction torun;          // Список функций к запуску в основном потоке(отображение? диспетчер)
    
    mapListPModule modules;          // Классы потоков
//    messagelist* msglist;                           // Структура с сообщениями - в родительском классе
    //	Mem* M;
    //	char* reserv;
    struct returnMod{ std::string path; std::string namemod; int number; int correct;};
    struct returnMes{ std::string frommod; std::string tomod; std::string nammes;  int correct;};

public:
    dispatcher(int,char**); 
    //< Конструктор принимает параметры программы
    dispatcher(inputString); 
    //< Конструктор принимает список запускаемых модулей

    int start();
    //< Запуск всех процессов происходит отдельно - умышленно.
    int addThread(returnMod);
    
    int addThread(std::thread*,std::string = "");
//    int remThread(std::thread* = 0);  // Мы врятле будем знать идентификатор процесса
      // а определить функцию (std::thread*=0,std::string) нельзя.
    int remThread(std::string);

    int addMess(returnMes);
    
    int stop(std::string);  
    //< Остановить выбранный процесс
    int stop();
    //< Остановить все процессы
    int tic(std::string);   
    //< Один тик выбранного процесса
    int tic();              
    //< Один тик всех процессов
    
private:
    returnMod parserModules(std::string);
    returnMes parserMessages(std::string);
    //< Поиск нужного процесса. Возвращает указатель на процесс в случае успеха и 0 иначе.
};

#endif