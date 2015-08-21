/* 
 * File:   lib.h
 * Author: utop
 *
 * Created on 9 июля 2015 г., 16:31
 */

#ifndef LIB_H
#define	LIB_H

#include <cstdint>
#include <map>
#include <queue>
#include <fstream>
#include <thread>
#include <ctime>    // Для выработки тиков - все модули их получают
#include <mutex>


#define _LIBCPP_IOSTREAM // Запрет подключать <iostream>  в модулях

// попробовать сделать через неблокирующие очереди

typedef void* dataType;

struct message{
    // Тип списка сообщений - неблокирующие очереди
    std::string from;
    std::string to;
    std::int8_t ID;
    std::int32_t size;
    dataType data;
    message(const message &msg){
        from = msg.from;
        to   = msg.to;
        ID   = msg.ID;
        size = msg.size;
        data = msg.data;
        
    }
    message(std::string from_, std::string to_, std::int8_t ID_, std::int32_t size_,void* data_):
            from(from_),to(to_),ID(ID_),size(size_),data(data_){};
};

struct Messager{
// Список сообщений между двумя потоками
private:
    std::mutex          lock; // локатор 
    std::queue<message> list; // очередь

public:
    Messager(std::string namemes_):namemes(namemes_){};
    
    message* get(){ 
        message* output = 0;
        if(lock.try_lock()){
            if(!empty()){
            output = new message(list.front()); // Конструктор копирования
            list.pop();}
            lock.unlock();
        }else return 0;
        return output;
    };
    
    std::int8_t  put(const message &msg){
        if(lock.try_lock()){
        list.push(msg);
        lock.unlock();
        }else
            return 1;
        return 0;
    };
    std::int8_t  empty()// Проверка на наличие сообщений
    {return list.empty();};       // 1 если пуст, 0 если не пуст
    
    std::int32_t size(){return list.size();};
    
    std::string namemes;
    std::string from;
    std::string to;
    
};


typedef std::map<std::string,Messager*> msgertype;

struct module{
// Заготовка/шаблон для создания классов модулей
// Назначение: передаваться в диспетчер для вызова деструктора
    msgertype messagelist; // Список сообщений для этого модуля
    
    module(){name = "NULL";logFileName = ".test_log_file";};
    virtual ~module(){};
    
    void openLogFile(){
        logFile.open(logFileName,std::ios_base::out | std::ios_base::ate);
        logFile<<"";
        logFile.close();
    }
    //> Печать в лог-файл
    void printLogFile(std::string str=""){
        logFile.open(logFileName,std::ios_base::app); //  | std::ios_base::ate | std::ios_base::trunc ,std::ios_base::out
        if(logFile.is_open()) logFile<<str;
//        logFile.flush();
        logFile.close();
    };
    //> Закрытие лог-файла
    
    virtual void tic() = 0;  // абстрактный класс
    
    std::fstream    logFile;
    std::string     logFileName;
    std::string     name; //< Имя модуля.
   
};

#endif	/* LIB_H */
