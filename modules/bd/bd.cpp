#include "bd.h"

DataBase* database = new DataBase();


void bd::start(){
    while(true){
        if(database){
            database->tic();
        }
        else return;
    }
}

DataBase::DataBase()
{
    name = "bd";
    logFileName = ".Data_Base_log";
    openLogFile();
};
     

DataBase::~DataBase(){
    name = "NULL";
};

void DataBase::tic(){
    message* tic_msg = 0;
    std::clock_t* _tic = 0;
//    while(true){
//        printLogFile("DataBase::tic size " + std::to_string(messagelist.size()) + " \n");
//        printLogFile("DataBase::tic tic_bd " + std::to_string(reinterpret_cast<long>(messagelist["tic_bd"])) + " \n");
//        printLogFile("DataBase::tic tic_bd size" + std::to_string(messagelist["tic_bd"]->size()) + " \n");
        if(messagelist.size() && messagelist["tic_bd"] && !messagelist["tic_bd"]->empty()){
        tic_msg = messagelist["tic_bd"]->get();
        if(tic_msg != 0){
            _tic = static_cast<std::clock_t*>(tic_msg->data);
            
            printLogFile("cur_tic : " + std::to_string(*_tic) + "\n");
            delete _tic; // Освобождение области памяти *data
            delete tic_msg; // Освобождение области памяти сообщения
        }
        else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
};
