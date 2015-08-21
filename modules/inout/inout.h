// Модуль отображения

#ifndef __INOUT_H
#define __INOUT_H
#include "lib.h"

#include "math.h"


namespace inout{
    void start_main();
    void start();
}

class InputOutput: public module{
    
public:
    InputOutput();
    ~InputOutput();
        
    void tic();
};

//#include "widget.h"

#endif