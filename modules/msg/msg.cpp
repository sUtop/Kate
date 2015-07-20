#include "msg.h"

MessageDispeather* messager = new MessageDispeather();


void msg::start(){
//    std::cout<<":MSG started\n";
    
    for (int i = 0; i < 30; ++i)
    {
        std::string str = "::MSG";
        messager->printLogFile(str+ "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


MessageDispeather::MessageDispeather(){
    name = "msg";
    logFileName = ".Message_Dispeather_log";
    openLogFile();
 };


MessageDispeather::~MessageDispeather(){
    name = "NULL";
};


//int messageDispeather::send(messagelist* (*from)(),void (*to)(messagelist*)){
//    
//    messagelist* tmp = (*from)();
//    (*to)(tmp);
//};

