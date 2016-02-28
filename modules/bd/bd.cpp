#include "bd.h"

#include <iostream>

int start(msgertype * msg) {

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    bd::DataBase* database = new bd::DataBase(msg, "bd");

    if (database == 0) return -1;

    std::cout << " Hi !! I'm BD!\n";
    while (true) {
        database->tic();
    }
    return 0;
}

bd::DataBase::DataBase(msgertype * msg, std::string name) :
Module(msg, name) {
};

bd::DataBase::~DataBase() {
};

void bd::DataBase::tic() {

    //    printLogFile("Hello !\n");

    Message* tic_msg = 0;
    if (mp_messagelist->size()) {
        for (std::map<std::string, Messager*>::iterator
            it = mp_messagelist->begin(); it != mp_messagelist->end(); ++it) {
            tic_msg = it->second->get();
            if (tic_msg) {
                std::cout << "BD::tic Get mes " << it->second->size() << " \n";;
                std::auto_ptr<std::clock_t> tic_(static_cast<std::clock_t*> (tic_msg->m_data));
                std::auto_ptr<Message> mes(static_cast<Message*> (tic_msg));
                printLogFile("cur_tic : " + std::to_string(*tic_) + "\n");
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

    //    if(mp_messagelist.size() && mp_messagelist["tic_bd"] && !mp_messagelist["tic_bd"]->empty()){
    //        tic_msg = mp_messagelist["tic_bd"]->get();
    //        if(tic_msg != 0){
    //            // auto_ptr - автоматически освобождает память
    //            std::auto_ptr<std::clock_t> tic_(static_cast<std::clock_t*>(tic_msg->data));
    //            std::auto_ptr<Message> mes(static_cast<Message*>(tic_msg));
    //            
    //            printLogFile("cur_tic : " + std::to_string(*tic_.get()) + "\n");
    //        }
    //        else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //    }
    //    else  std::this_thread::sleep_for(std::chrono::milliseconds(10));

};

