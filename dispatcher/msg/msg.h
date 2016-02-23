// 

/*! \brief Модуль диспетчеризации сообщений.
 *  \autor Utop 
 *
 Имя:
    msg.h
 Описание:
 *  !!! Все-таки двойная вложенность сообщений!
 *      Как поток только отсылает всем тики, запускается в диспетчере последним
 *          Сообщения связанны в момент после считывания конфигурации
 *          все "от" привязанны "к".
 **/


#ifndef __MSG_H
#define __MSG_H

#include <mutex>    // остановка потоков при одновременном использовании
#include <thread>
//#include <atomic> // !!! TODO добавить атомарность посылки сообщений

#include "lib.h"

namespace msg {
    void start(msgertype * messagelist);
}



class MessageDispeather : private Module {
    //    std::clock_t    curr_tic;
    std::time_t curr_tic;
public:
    mapThreadFunctions pf_tic; //< Список функций для запуска по тику
    //    msgertype 
    //    Messager
    MessageDispeather(msgertype *);
    ~MessageDispeather();
    void tic();

    //    int send(messagelist* (*from)(),void (*to)(messagelist*));

    // для отправки сообщения вызывается send
    // в качестве параметров должны передаваться функции метода отправителя
    // и метода получателя (функции отправки и распаковки сообщения соответственно)
    // внутри модуля сообщения должны быть помещенны в очереди.
    // Возможные вызовы - 1. по таймеру диспетчером (функция from вызывается много раз), 
    //  2. по запросу отправителя - функция from вызывается один раз

};


#endif