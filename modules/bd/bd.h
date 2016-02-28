// Модуль управления базой данных

#ifndef __BD_H
#define __BD_H

#include "lib.h"

extern "C" int start(msgertype * msg);

namespace bd {

    class DataBase : private Module {
        
        // Пока концепция - записывать все в файлы
        
        typedef std::map<std::string, std::fstream> data_type;
        data_type m_files; //!< Список файлов с данными
        
        
    public:
        //! Конструктор, принимает уготованную ему очередь сообщений и 
        // собственное имя для возможности записи лог-файла.
        explicit DataBase(msgertype *, std::string);
        ~DataBase();

        //    int send(messagelist* (*from)(),void (*to)(messagelist*));

        // для отправки сообщения вызывается send
        // в качестве параметров должны передаваться функции метода отправителя
        // и метода получателя (функции отправки и распаковки сообщения соответственно)
        // внутри модуля сообщения должны быть помещенны в очереди.
        // Возможные вызовы - 1. по таймеру диспетчером (функция from вызывается много раз), 
        //  2. по запросу отправителя - функция from вызывается один раз

        void tic();
    };

}

#endif