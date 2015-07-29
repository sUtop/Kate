#include "bd.h"

DataBase* database = new DataBase();


void bd::start(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 
    for (int i = 0; i < 3; ++i)
    {
        std::string str = "::BD  ";
        database->printLogFile(str + std::to_string(i) + "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
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
    while(true){
        tic_msg = messagelist["tic_bd"]->get();
        if(tic_msg){
            printLogFile("get tic \n");
            _tic = static_cast<std::clock_t*>(tic_msg->data);
            printLogFile("cur_tic : " + std::to_string(*_tic) + "\n");
            delete _tic; // Освобождение области памяти *data
//            printLogFile("delete _tic \n");
            delete tic_msg; // Освобождение области памяти сообщения
//            printLogFile("delete tic_msg \n");
        }
        else  std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
};
