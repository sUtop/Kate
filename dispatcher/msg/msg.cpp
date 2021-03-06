#include "msg.h"

// Мессаджер один и создается при запуске (см диспетчер).
msg::MessageDispeather* messager;

void msg_start(mapArgFunctions * mlist) {

    messager = new msg::MessageDispeather(mlist);
    ;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true) {
        if (messager) {
            messager->tic();
        } else return;
    }
}

msg::MessageDispeather::MessageDispeather(mapArgFunctions * msg) :
Module(0, "msg"), // // ! Родителю не передается список сообщений - ибо нефиг
m_mes(msg) {
    //    curr_tic = std::clock();
    std::time(&curr_tic);
};

msg::MessageDispeather::~MessageDispeather() {
    //    m_name = "NULL";
};

void msg::MessageDispeather::tic() {


    if (m_mes) {


        std::time_t time;
        //    std::TDateTime;
        std::time(&time);
        if (time > curr_tic) {
            curr_tic += 5; //std::chrono::seconds(1);//500000; // минимум - 1 секунда


            //typedef std::map<std::string, Messager*> msgertype;
            //typedef std::map<std::string, msgertype *> mapArgFunctions;

            for (auto it = m_mes->begin(); it != m_mes->end(); ++it) {
                if (it->first == "bd") {

                    for (auto i = it->second->begin(); i != it->second->end(); ++i)
                        if (i->first == "tic_bd") {

                            std::clock_t* _tic = new std::clock_t(std::clock()); // Область памяти *data
                            printLogFile("tic:: bd tic " + std::to_string(*_tic) + " sended \n");
                            
                            Message tic_msg("msg", "ANY", 0, sizeof (std::clock_t*), static_cast<dataType> (_tic));
                            for (; i->second->put(tic_msg);) {
                            }; // Пока не освободится

                        }
                }
            }


            //        for (msgertype::const_iterator i = mp_messagelist->begin(); i != mp_messagelist->end(); ++i) {
            //            std::clock_t* _tic = new std::clock_t(std::clock()); // Область памяти *data
            //            Message tic_msg("msg", "ANY", 0, sizeof (std::clock_t*), static_cast<dataType> (_tic));

            //            if (i->first == "tic_inout") {
            //                for (; i->second->put(tic_msg);) {
            //                }; // || i->first == "tic_phz"
            //                    printLogFile("Send tic inout to \t " + std::to_string(long (i->second)) + "\n");
            //            }

            //            if (i->first == "tic_bd") {
            //                for (; i->second->put(tic_msg);) {
            //                }; // Пока не освободится
            //                    printLogFile("Send tic bd to  \t " + std::to_string(long (i->second)) + "\n");                    
            //            }
            //        }


            //        printLogFile(std::to_string(pf_tic.size()) + " size \n");
            for (mapThreadFunctions::iterator i = pf_tic.begin(); i != pf_tic.end(); ++i) {
                printLogFile((i->first) + " sended \n");
                //            i->second(); // !! Вызов функции ???
            }
        } else std::this_thread::sleep_for(std::chrono::milliseconds(100));


    };
};

//struct Message{
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
//    for(;j!=threads.end();++j){
//        j->messagelist["tic"] = msg;


//int messageDispeather::send(messagelist* (*from)(),void (*to)(messagelist*)){
//    
//    messagelist* tmp = (*from)();
//    (*to)(tmp);
//};

