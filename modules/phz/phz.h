// Модуль обработки физики

#ifndef __PHZ_H
#define __PHZ_H

#include "lib.h"

extern "C" int start(msgertype * msg);

namespace phz {

    class Physics : private Module {
    public:
        //! Конструктор, принимает уготованную ему очередь сообщений и 
        // собственное имя для возможности записи лог-файла.
        explicit Physics(msgertype *, std::string);
        ~Physics();

        void tic();

    };
};

#endif