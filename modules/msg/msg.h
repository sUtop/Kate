// Модуль диспетчеризации сообщений

#ifndef __MSG_H
#define __MSG_H

#include <mutex>
#include <thread>
#include <atomic> // !!! TODO добавить атомарность посылки сообщений

#include "lib.h"

namespace msg{
    void start();
    
}

class MessageDispeather: public module{


    
public:
//    msgertype 
//    Messager
    MessageDispeather();
    ~MessageDispeather();
    
//    int send(messagelist* (*from)(),void (*to)(messagelist*));
    
    // для отправки сообщения вызывается send
    // в качестве параметров должны передаваться функции метода отправителя
    // и метода получателя (функции отправки и распаковки сообщения соответственно)
    // внутри модуля сообщения должны быть помещенны в очереди.
    // Возможные вызовы - 1. по таймеру диспетчером (функция from вызывается много раз), 
    //  2. по запросу отправителя - функция from вызывается один раз
    
};

#endif