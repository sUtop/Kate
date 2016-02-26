#include "phz.h"

//Physics* physics = new Physics();

void phz::start(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
//    for (int i = 0; i < 40; ++i)
//    {
//        std::string str = "::PHZ  ";
//        physics->printLogFile(str + std::to_string(i) + "\n");
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    }
}

Physics::Physics(msgertype * msg, std::string name)
: Module(msg, name){
};

Physics::~Physics(){
};

void Physics::tic(){

};
