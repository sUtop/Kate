/*! \brief Общее для всех модулей АПИ.
 *  \autor Utop 
 *
 Имя:
    lib.cpp
 Описание:
 *     Библиотечный модуль реализация методов классов.
 * 
 * Created on 9 июля 2015 г., 16:31
 */


#include "lib.h"


Message::Message(const Message &msg) {
    m_from = msg.m_from;
    m_to = msg.m_to;
    m_ID = msg.m_ID;
    m_size = msg.m_size;
    m_data = msg.m_data;

};

Message::Message(std::string from_, std::string to_, std::int8_t ID_, std::int32_t size_, void* data_) :
m_from(from_), m_to(to_), m_ID(ID_), m_size(size_), m_data(data_) {
};

Messager::Messager(std::string namemes_) : namemes(namemes_) {
};

Message* Messager::get() {
    Message* output = 0;
    if (lock.try_lock()) {
        if (!empty()) {
            output = new Message(list.front()); // Конструктор копирования
            list.pop();
        }
        lock.unlock();
    } else return 0;
    return output;
};

std::int8_t Messager::put(const Message &msg) {
    if (lock.try_lock()) {
        list.push(msg);
        lock.unlock();
    } else
        return 1;
    return 0;
};

std::int8_t Messager::empty()// Проверка на наличие сообщений
{
    return list.empty();
}; // 1 если пуст, 0 если не пуст

std::int32_t Messager::size() {
    return list.size();
};

Module::Module(msgertype * msg, std::string name_) {
    m_name = name_;
    m_logFileName = "." + m_name + "_log_file";
    mp_messagelist = msg;
};

Module::~Module() {
};

void Module::openLogFile() {
    try {
        m_logFile.open(m_logFileName, std::ios_base::out | std::ios_base::ate);
        m_logFile << "";
        m_logFile.close();
    } catch (...) {
        ;
    };
};
//> Печать в лог-файл

void Module::printLogFile(std::string str = "") {
    try {
        m_logFile.open(m_logFileName, std::ios_base::app); //  | std::ios_base::ate | std::ios_base::trunc ,std::ios_base::out
        //            if(logFile.is_open()) 
        m_logFile << str;
        m_logFile.close();
    } catch (...) {
        ;
    }
};

