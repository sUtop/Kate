#include "msg.h"

void msg::start(){
    std::cout<<":MSG started\n";
//    long double k[10000];

    
    for (int i = 0; i < 30; ++i)
    {
        std::string str = "::MSG";
        std::cout<<str<<"\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
//    k[777]++;
    
}

int messageDispeather::send(message* (*from)(),void (*to)(message*)){
    
    message* tmp = (*from)();
    (*to)(tmp);
};

