#include "bd.h"


int start( msgertype * msg){
    bd::DataBase* database = new bd::DataBase(msg,"Bd");

    if(database == 0) return -1;
    
    while(true){
            database->tic();
    }
    return 0;
}

bd::DataBase::DataBase(msgertype * msg, std::string name): 
    Module(msg,name) {
};
     

bd::DataBase::~DataBase(){
};

void bd::DataBase::tic(){

//    Message* tic_msg = 0;
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
