// Модуль отображения

#ifndef __INOUT_H
#define __INOUT_H
#include "lib.h"

#include "math.h"

//extern "C" int start_main(msgertype * msg);
extern "C" int start(msgertype * msg);

namespace inout {

    class InputOutput : public Module {
    public:
        explicit InputOutput(msgertype *, std::string);
        ~InputOutput();

        void tic();
    };
}

//#include "widget.h"

#endif