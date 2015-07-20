#include "inout.h"

InputOutput *inputoutput = new InputOutput();

void inout::start(){
//    std::cout<<":OUT started\n";
    for (int i = 0; i < 60; ++i)
    {
        std::string str = "::OUT";
        inputoutput->printLogFile(str + "\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
};


InputOutput::InputOutput(){
    name = "inout";
    logFileName = ".Input_Output_log";
    openLogFile();
};

InputOutput::~InputOutput(){
    name = "NULL";
};
