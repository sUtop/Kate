#include "msg.h"

MessageDispeather* messager = new MessageDispeather();


void msg::start(){
//    std::cout<<":MSG started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    for (int i = 0; i < 3; ++i)
    {
        std::string str = "::MSG  ";
        messager->printLogFile(str + std::to_string(i) +  "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    
    while(true){
        if(messager){
            messager->tic();
        }
        else return;
        
    }

    
}


MessageDispeather::MessageDispeather(){
    name = "msg";
    logFileName = ".Message_Dispeather_log";
    openLogFile();
    curr_tic = std::clock();
 };


MessageDispeather::~MessageDispeather(){
    name = "NULL";
};

void MessageDispeather::tic(){
    if(std::clock() - curr_tic > 1000){
        curr_tic += 1000;
        std::clock_t* _tic = new std::clock_t(std::clock()); // Область памяти *data

        message tic_msg("msg","ANY",0,sizeof(std::clock_t*),
                static_cast<dataType>(_tic));
        messagelist["tic_bd"]->put(tic_msg);
        printLogFile("Send tic N" + std::to_string(*_tic) + "\n");
//            messagelist["tic_inout"]->put(tic_msg);
//            messagelist["tic_phz"]->put(tic_msg);
    }
    else  std::this_thread::sleep_for(std::chrono::milliseconds(100));

};

            //struct message{
            //    // Тип списка сообщений - неблокирующие очереди
            //    std::string from;
            //    std::string to;
            //    std::int8_t ID;
            //    std::int32_t size;
            //    void* data;
    
            //# Тики - 1/32 секунды
            //msg:"msg"->"bd":"tic_bd"
            //msg:"msg"->"inout":"tic_inout"
            //msg:"msg"->"phz":"tic_phz"
            // Потом будет вызываться:
            //   module.messagelist["mesname"].put(message) в коде будет выглядить  messagelist["mesname"].put(message)
            // и module.messagelist["mesname"].get(message)                         messagelist["mesname"].get(message)
            // + module.messagelist["mesname"].isempty()                            messagelist["mesname"].isempty()
            // + module.messagelist["mesname"].clear                                messagelist["mesname"].clear()
            // 
            //    msgertype* msg = new msgertype("tic") ??? или msg = messager.tic
            //    std::map<std::string,std::thread*>::iterator j = threads.begin();
            //    for(;j!=threads.end();j++){
            //        j->messagelist["tic"] = msg;


//int messageDispeather::send(messagelist* (*from)(),void (*to)(messagelist*)){
//    
//    messagelist* tmp = (*from)();
//    (*to)(tmp);
//};

