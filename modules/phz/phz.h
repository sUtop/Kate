// Модуль обработки физики

#ifndef __PHZ_H
#define __PHZ_H

#include "lib.h"

namespace phz{
    void start();
}

class Physics: public Module{
    
    
    
public:
    //! Конструктор, принимает уготованную ему очередь сообщений и 
    // собственное имя для возможности записи лог-файла.
    explicit Physics(msgertype *, std::string) ;
    ~Physics();
    
    void tic();
    
};

#endif