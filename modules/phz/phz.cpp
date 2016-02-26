#include "phz.h"


#include <iostream>

int start(msgertype * msg)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    phz::Physics* phzi = new phz::Physics(msg, "phz");

    if(phzi == 0) return -1;

    std::cout << " Hi !! I'm BD!\n";
    //    while(true){
    phzi->tic();
    //    }
    return 0;



    //    phz::Physics* physics = new phz::Physics(msg,"phz");
    //    physics->printLogFile("Hello !");
    //    for (int i = 0; i < 40; ++i)
    //    {
    //        std::string str = "::PHZ  ";
    //        physics->printLogFile(str + std::to_string(i) + "\n");
    //        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //    }
}

phz::Physics::Physics(msgertype * msg, std::string name)
: Module(msg, name)
{
};

phz::Physics::~Physics()
{
};

void phz::Physics::tic()
{

    printLogFile("Hello ?\n");

};
