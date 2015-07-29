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
        
static void update();
};

//#include "widget.h"

#endif