#include "phz.h"

void phz::start(){
    std::cout<<":PHZ started\n";
    
    for (int i = 0; i < 40; ++i)
    {
        std::string str = "::PHZ";
        std::cout<<str<<"\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}