/*! \brief Модуль управления потоками.
 *  \autor Utop 
 *
 Имя:
    dispather.cpp
 Описание:
   Модуль диспетчера не обязан знать где и какие модули лежат.
   Эту информацию он получает из конфигурационного файла. 
   В каждом модуле он вызывает в отдельном потоке функцию "start", 
   которая запускает бесконечный цыкл. В качестве параметра передается список 
   сообщений для этого модуля. В цыкле этот модуль обрабатывает переданные 
   ему сообщения. Для добавления очереди сообщений - необходимо описать их
   в конфигурационном файле.
 **/

// 

#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include <list>
#include <iostream>
#include <string>
#include "lib.h"

#include "msg.h"
extern msg::MessageDispeather *messager;

/* \brief Диспетчер потоков.
 *   Динамически вызывает модули, читает конфигурацию, создает потоки сообщений
 *      и сцепляет модули посредством их.
 */
class dispatcher {

        /* \brief Структура для чтения модуля из конфигурации.
     */
    struct returnMod {
        std::string path; //!< путь до библиотеки
        std::string namemod; //!< имя модуля
        int number; //!< количество запусков модуля
        //       (0) - для запуска в главном потоке
        //       (N) - для запуска N потоков паралельно
        int correct; //!< признак корректности считывания модуля, выставляется последним

        returnMod() : path(""), namemod(""), number(0), correct(-1) {
        }
    };

        /* \brief Структура для чтения сообщения из конфигурации.
     */
    struct returnMes {
        std::string frommod; //!< Источник сообщения
        std::string tomod; //!< Получатель сообщения
        std::string nammes; //!< Имя сообщения
        int correct; //!< признак корректности считывания модуля, выставляется последним

        returnMes() : frommod(""), tomod(""), nammes(""), correct(-1) {
        }
    };

    typedef std::list<std::thread*> thredList;
    //!< Список запущенных потоков


public:

    typedef std::list<std::string, std::allocator<std::string> > inputString;
    //!< Строки с конфигурацией

    dispatcher(inputString);
    //!< Конструктор принимает список запускаемых модулей
    int start();
    //!< Запуск всех процессов происходит отдельно - умышленно.
    int addThread(returnMod &);
    //!< Добавление потока 

    //    int remThread(std::thread* = 0);  // Мы врятле будем знать идентификатор процесса
    // а определить функцию (std::thread*=0,std::string) нельзя.
    int remThread(std::string);
    //!< Удаление потока по имени ? 

    ~dispatcher();
    
//    int addMess(returnMes &);
    //!< Добавление типа сообщения в список

/*    
    int stop(std::string);
    //!< Остановка выбранного процесса
    int stop();
    //!< Остановить все процессы
    int tic(std::string);
    //!< Один тик выбранного процесса
    int tic();
    //!< Один тик всех процессов

   // !! В текущей идеологии происходит посредством очередей
*/    
private:

    returnMod parserModules(std::string);
    //!< Поиск в строке информации о подключаемом модуле
    //!< Поиск нужного процесса. Возвращает указатель на процесс в случае успеха и 0 иначе.
    returnMes parserMessages(std::string);
    //!< Поиск в строке информации о добавляемом сообщении

    
    typedef std::map<std::string, thredList *> mapListsThreads;
    //!< Список списков потоков ("список списков", двоение - для множественного запуска)
    
    mapListsThreads m_threads; // Список потоков
    mapThreadFunctions m_toRun;
    // Список функций к запуску в основном потоке(отображение? диспетчер)
    mapArgFunctions m_argsToRun; // ( )
    //!< Список аргументов для функций на запуск (сообщения)
    // Так же отвечает за хранение всех сообщений.


    //    mapListPModule modules; // Классы потоков


};

#endif