/*! \brief Общее для всех модулей АПИ.
 *  \autor Utop 
 *
 Имя:
    lib.h
 Описание:
 *  Структура сообщений список сообщений и базовый класс для модулей.
 * 
 *  Модуль - динамически подключаемая библиотека.
 *      при чтении конфигурации подключается библиотека и 
 *      вызывается метод start(*messagelist) - столько раз, сколько потоков
 *      требуется в конфигурационном файле.
 *  Очередь сообщений messagelist - создается до запуска потока и передается
 *      в качестве параметра для подключения ее к потоку.
 * 
 *  Описание структуры сообщения и находятся в этом заголовке:
 *      1. Для того, чтобы все модули могли ими пользоваться
 *      2. Так как сам Мессаджер тоже является модулем и запускается наравне 
 *          с остальными.
 *  
 * Created on 9 июля 2015 г., 16:31
 */

#ifndef LIB_H
#define	LIB_H

//#include <cstdint>
#include <map>
#include <queue>
#include <fstream>
#include <thread>
#include <ctime>    // Для выработки тиков - все модули их получают
#include <mutex>
#include <memory>
#include <exception>

#include <list>

#define _LIBCPP_IOSTREAM // Запрет подключать <iostream>  в модулях

// попробовать сделать через неблокирующие очереди

typedef void* dataType;


//!< Одно сообщение с информацией.

struct Message {
    // Тип списка сообщений - неблокирующие очереди
    // Атомарные операции введены в стандарт С11!
    std::string m_from; // Источник
    std::string m_to; // Получатель
    std::int8_t m_ID; // Некоторый идентификатор
    std::int32_t m_size; // Размер
    dataType m_data;
    Message(const Message &msg);

    Message(std::string from_, std::string to_,
            std::int8_t ID_, std::int32_t size_, void* data_);
};

//!< Одна очередь сообщений между двумя потоками
class Messager {
    std::mutex lock; // локатор 
    std::queue<Message> list; // очередь

public:
    Messager(std::string namemes_);
    Message* get();

    std::int8_t put(const Message &msg);
    std::int8_t empty();
    std::int32_t size();

    std::string namemes;
    std::string from;
    std::string to;

};


typedef std::map<std::string, Messager*> msgertype;
//!< Все очереди сообщений ко всем модулям

typedef int (*start_function)(msgertype *);
//!< Указатель на функцию для запуска (start_function) передается 

//typedef std::map<std::string, start_function> pftype;
////!< Список указателей на функции для запуска.

typedef std::map<std::string, start_function> mapThreadFunctions;
//!< Список функций на запуск


/* \brief Базовый для всех модулей родитель.
 *  Хранит имя модуля и открытый файл логов.
 *      Назначение: передаваться в диспетчер для вызова деструктора.
 */
class Module {
    std::fstream m_logFile; //!< Открытый файл для логирования.
    std::string m_logFileName; //!< Имя файла логирования
    std::string m_name; //!< Имя модуля.


    void openLogFile(); //!< Закрытие лог-файла
    explicit Module(); //!< Умолчательный конструктор запрещен
    Module(Module&); //!< Конструктор копирования запрещен
    Module &operator=(const Module&); //!< Оператор присваивания запрещен
public:
    //! Конструктор, принимает уготованную ему очередь сообщений и 
    // собственное имя для возможности записи лог-файла.
    explicit Module(msgertype *, std::string);
    virtual ~Module();
    virtual void tic() = 0; // абстрактный классk                                   



    void printLogFile(std::string str); //!< Печать в лог-файл

    const std::string &name();
    msgertype * mp_messagelist; //!< Список сообщений для этого модуля

};

#endif	/* LIB_H */
