// Модуль управления потоками

#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include <thread>
#include <map>
#include <list>
#include <string>
#include "lib.h"

// Модуль диспетчера не обязан знать где и какие модули лежат
// однако как это сделать пока непонятно. Поэтому
// временное решение - прямое включение модулей.
#include "modules/msg/msg.h"
extern MessageDispeather *messager;
#include "modules/bd/bd.h"
extern DataBase *database;
#include "modules/inout/inout.h"
extern InputOutput *inputoutput;
#include "modules/phz/phz.h"
extern Physics *physics;


class dispatcher{
    //	Thread* Th;
    std::map<std::string,std::thread*> threads;     // Список потоков
    std::map<std::string,module*> modules;          // Классы потоков
//    messagelist* msglist;                           // Структура с сообщениями - в родительском классе
    //	Mem* M;
    //	char* reserv;

public:
    dispatcher(int,char**); 
    //< Конструктор принимает параметры программы
    dispatcher(std::list<std::string>); 
    //< Конструктор принимает список запускаемых модулей

    int start();
    //< Запуск всех процессов происходит отдельно - умышленно.
    int addThread(std::thread*,std::string = "");
//    int remThread(std::thread* = 0);  // Мы врятле будем знать идентификатор процесса
      // а определить функцию (std::thread*=0,std::string) нельзя.
    int remThread(std::string);
    
    int stop(std::string);  
    //< Остановить выбранный процесс
    int stop();
    //< Остановить все процессы
    int tic(std::string);   
    //< Один тик выбранного процесса
    int tic();              
    //< Один тик всех процессов
    
private:
    std::thread* parserModules(std::string);
    void parserMessages(std::string);
    //< Поиск нужного процесса. Возвращает указатель на процесс в случае успеха и 0 иначе.
};

#endif