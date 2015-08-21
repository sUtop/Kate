#include "msg.h"

MessageDispeather* messager = new MessageDispeather();


void msg::start(){
        std::this_thread::sleep_for(std::chrono::seconds(10));
    
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
//    curr_tic = std::clock();
    std::time(&curr_tic);
 };


MessageDispeather::~MessageDispeather(){
    name = "NULL";
};

void MessageDispeather::tic(){
    std::time_t time;
//    std::TDateTime;
    std::time(&time);
    if( time > curr_tic ){
        curr_tic++; //std::chrono::seconds(1);//500000; // минимум - 1 секунда

       
        for(msgertype::const_iterator i=messagelist.begin();i!=messagelist.end();i++){
                std::clock_t* _tic = new std::clock_t(std::clock()); // Область памяти *data
                message tic_msg("msg","ANY",0,sizeof(std::clock_t*),static_cast<dataType>(_tic));
                if(i->first == "tic_inout"){
                    for(;i->second->put(tic_msg);){}; // || i->first == "tic_phz"
//                    printLogFile("Send tic inout to \t " + std::to_string(long (i->second)) + "\n");
                }
                if(i->first == "tic_bd"){
                    for(;i->second->put(tic_msg);){}; // Пока не освободится
//                    printLogFile("Send tic bd to  \t " + std::to_string(long (i->second)) + "\n");                    
                }
        }
        
//        printLogFile(std::to_string(pf_tic.size()) + " size \n");
        for(std::map<std::string,PFunction>::const_iterator i = pf_tic.begin();i!=pf_tic.end();i++)
        {
            printLogFile((i->first) + " sended \n");
            i->second();
        }
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
    
            //# Тики - 1 секунда
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

