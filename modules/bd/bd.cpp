#include "bd.h"

DataBase* database = new DataBase();


void bd::start(){
 
    for (int i = 0; i < 100; ++i)
    {
        std::string str = "::BD";
        database->printLogFile(str+ "\n" + std::to_string(i) + "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

