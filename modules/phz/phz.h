// Модуль обработки физики

#ifndef __PHZ_H
#define __PHZ_H

#include "lib.h"

namespace phz{
    void start();
}

class Physics: public module{
    
    
    
public:
    Physics();
    ~Physics();
    
    void tic();
    
};

#endif