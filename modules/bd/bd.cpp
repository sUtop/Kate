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
    if(messagelist.size() && messagelist["tic_bd"] && !messagelist["tic_bd"]->empty()){
        tic_msg = messagelist["tic_bd"]->get();
        if(tic_msg != 0){
            // auto_ptr - автоматически освобождает память
            std::auto_ptr<std::clock_t> tic_(static_cast<std::clock_t*>(tic_msg->data));
            std::auto_ptr<message> mes(static_cast<message*>(tic_msg));
            
            printLogFile("cur_tic : " + std::to_string(*tic_.get()) + "\n");
        }
        else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
};
