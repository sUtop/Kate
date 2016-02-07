#include "inout.h"
#include "widget.h" // ! Нельзя включать в хидере
#include "sender.h"

InputOutput *inputoutput = new InputOutput();

char* argv[] = {"./Kate",""};
int argc = 1;

QApplication MainApp(argc,argv);
Widget w(0);
sender sendarman;

void inout::start_main(){

    inputoutput->printLogFile("create QApplication \n");
    w.show();
    inputoutput->printLogFile("show widget \n");

    MainApp.exec();
    inputoutput->printLogFile("exec \n");
    
};

void inout::start(){
    sendarman.addconnect(w);
    
    while(true){
        inputoutput->tic();
    };
};

InputOutput::InputOutput(){
    name = "inout";
    logFileName = ".Input_Output_log";
    openLogFile();
};

InputOutput::~InputOutput(){
    name = "NULL";
};

void InputOutput::tic(){
    message* tic_msg = 0;
//    std::clock_t* _tic = 0;

    if(messagelist.size() && messagelist["tic_inout"] && !messagelist["tic_inout"]->empty()){
        tic_msg = messagelist["tic_inout"]->get();
        if(tic_msg != 0){
            // auto_ptr - автоматически освобождает память
            std::auto_ptr<std::clock_t> tic_(static_cast<std::clock_t*>(tic_msg->data));
            std::auto_ptr<message> mes(static_cast<message*>(tic_msg));

            sendarman.sendtic(); // Связь по тику
        }
        else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    else  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
};
