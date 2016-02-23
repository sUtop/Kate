#include "inout.h"
#include "widget.h" // ! Нельзя включать в хидере
#include "sender.h"

inout::InputOutput *inputoutput;

char* argv[] = {"./Kate", ""};
int argc = 1;

QApplication MainApp(argc, argv);
Widget w(0);
sender sendarman;

//int start_main(msgertype * msg)
//{
//
//    inputoutput = new inout::InputOutput(msg,"inout");
//    inputoutput->printLogFile("create QApplication \n");
//    w.show();
//    inputoutput->printLogFile("show widget \n");
//
//    MainApp.exec();
//    inputoutput->printLogFile("exec \n");
//
//};

int start(msgertype * msg)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    w.show();
    MainApp.exec();
/// !!! Временно

    //    sendarman.addconnect(w);

    //    while(true){
    //        inputoutput->tic();
    //    };
};

inout::InputOutput::InputOutput(msgertype *msg, std::string name)
: Module(msg, name)
{
    name = "inout";
};

inout::InputOutput::~InputOutput()
{
};

void inout::InputOutput::tic()
{
    Message* tic_msg = 0;
    //    std::clock_t* _tic = 0;

//    if(mp_messagelist.size() && mp_messagelist["tic_inout"] && !mp_messagelist["tic_inout"]->empty()) {
//        tic_msg = mp_messagelist["tic_inout"]->get();
//        if(tic_msg != 0) {
//            // auto_ptr - автоматически освобождает память
//            std::auto_ptr<std::clock_t> tic_(static_cast<std::clock_t*> ( tic_msg->data ));
//            std::auto_ptr<Message> mes(static_cast<Message*> ( tic_msg ));
//
//            sendarman.sendtic(); // Связь по тику
//        }
//        else std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//    else std::this_thread::sleep_for(std::chrono::milliseconds(10));

};
