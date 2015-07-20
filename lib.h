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


#define _LIBCPP_IOSTREAM // Запрет подключать <iostream>  в модулях

//struct queItem{
//    void* data;
//    queItem* next;
//    queItem(queItem* message = 0)
//    {
//        data = message;
//        next = 0;
//    }
//};

//class message{
//    // Тип списка сообщений - неблокирующие очереди
//    std::string from;
//    std::string to;
//    std::int8_t ID;
//    std::int32_t size;
//    // очередь:  Каждый элемент ссылается на следующий, отправитель 
//    // кладет в last, получатель берет из first
//    atomic<queItem*>    first;
//    atomic<queItem*>    last;
//public:
//    message(std::int32_t size_):size(size_){
//          first = new queItem();
//          last = first;
//          // from = 
//          // to = 
//    };
//    void* get(){
//        if (first == last || first.next == 0){ return 0;}
//        void* mess = first.next.data;
//        first = first.next;
//        return mess;
//    };
//    std::int8_t put(void* data){
//          last.next = new queItem(data);
//          if(last.next) last = last.next;
//          else return 1; // ERROR - no memmory !!!
//          return 0;
//    };
//    
//    std::int8_t empty(){
//        return first != last;
//    }
//};

struct message{
    // Тип списка сообщений - неблокирующие очереди
    std::string from;
    std::string to;
    std::int8_t ID;
    std::int32_t size;
    void* data;
    message(const message &msg){
        from = msg.from;
        to   = msg.to;
        ID   = msg.ID;
        size = msg.size;
        data = msg.data;
        
    }
};

struct Messager{
// Список сообщений между двумя потоками
    std::mutex          lock; // локатор 
private:
    std::queue<message> list; // очередь

public:
    Messager(std::string namemes_):namemes(namemes_){};
    
    message* get(){ 
        message* output = 0;
        lock.lock();
        if(!list.empty()){
        output = new message(list.back()); // Конструктор копирования
        list.pop();}
        lock.unlock();
        return output;
    };
    
    std::int8_t  put(const message &msg){
        lock.lock();
        list.push(msg);
        lock.unlock();
        return 0;
    };
    std::int8_t  empty()// Проверка на наличие сообщений
    {return list.empty();};       // 1 если не пуст, 0 если пуст
    
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
    ~module(){};
    
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
    
    virtual void tic(){};
    
    std::fstream    logFile;
    std::string     logFileName;
    std::string     name; //< Имя модуля.
   
};

#endif	/* LIB_H */
