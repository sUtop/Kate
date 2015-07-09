#include "out.h"

void out::start(){
    std::cout<<":OUT started\n";

    for (int i = 0; i < 60; ++i)
    {
        std::string str = "::OUT";
        std::cout<<str<<"\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

};