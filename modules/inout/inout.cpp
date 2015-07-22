#include "inout.h"
#include "widget.h" // ! Нельзя включать в хидере
#include "math.h"


InputOutput *inputoutput = new InputOutput();

char* argv[] = {"./Kate",""};
int argc = 1;

QApplication MainApp(argc,argv); // глобальные в lib.h
Widget w(0);



// in main-function        
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//    
//    return a.exec();
        
        

void inout::start(){
//    std::cout<<":OUT started\n";
//    for (int i = 0; i < 10; ++i)
//    {
//        std::string str = "::OUT";
//        inputoutput->printLogFile(str + std::to_string(i) + "\n");
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    }
    
//    while(true){
//        if(inputoutput){
//            inputoutput->tic();
//        }
//        else return;
//    }

    inputoutput->printLogFile("\n create QApplication");
    inputoutput->printLogFile("\n create Widget");
    w.show();
    inputoutput->printLogFile("\n show widget");
//    
////    return 
    MainApp.exec();
    inputoutput->printLogFile("\n exec");
    
    inputoutput->tic();

    
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
    std::clock_t* _tic = 0;
//    while(true){
//        if(tic_msg = messagelist["tic_inout"]->get()){
//            printLogFile("get tic \n");
//            _tic = static_cast<std::clock_t*>(tic_msg->data);
//            printLogFile("cur_tic : " + std::to_string(*_tic) + "\n");
//            delete _tic; // Освобождение области памяти *data
//            delete tic_msg; // Освобождение области памяти сообщения
//        }
//        else  std::this_thread::sleep_for(std::chrono::milliseconds(20));

    
//    	auxInitDisplayMode(AUX_RGB);
//	auxInitPosition (0, 0, 500, 500);
//	auxInitWindow ("Step1");
        
//        int argc = 1; 
//        typedef char** ppchar;
//        ppchar argv = reinterpret_cast<ppchar>(new char[2][10]);
//        argv = new *char[1];
//        argv[0] = "./Kate";
//        argv[1] = "";

//        char *argv_[] = {"./Kate",""};
//      
    
    
//    NSApplicationMain(mainargc, (const char **)mainargv);
//        printLogFile(std::to_string(mainargc) + "   " + mainargv[0] + "\n");
        
// QMessageBox msgBox;
// msgBox.setText("The document has been modified.");
// msgBox.exec();
        
//    }
    
};

