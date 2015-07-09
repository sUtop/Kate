#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

#include "dispatcher.h"

std::list<std::string> to_start;

int ReadConfig(std::string is = ""){
    std::string tmp = is;
//    FILE fl;
    if(tmp==""){ tmp = "Kate.conf" ;};
    std::ifstream ConfigFile;
    ConfigFile.open(tmp);
    
    if(ConfigFile){
        while(tmp!=""){
//        std::cout<<tmp<<"\n";   
        getline(ConfigFile, tmp);
        to_start.push_back(tmp);
    /* TODO Обработка конфигурационного файла.*/};
    };
    ConfigFile.close();
    std::list<std::string>::const_iterator i = to_start.begin();
    for(;i!=to_start.end();i++)
        std::cout<<":"<<*i<<":"<<"\n";
    
    return 1;
};

int main(int argc,char** argv){
    std::cout<<" Kate started with params :\""<<argc<<"\""<<"\n";
    for(int i=0;i<argc;i++)
        std::cout<<"=\""<<argv[i]<<"\"\n";
    
    if(ReadConfig())
    {
        dispatcher* dsp = new dispatcher(to_start);
        dsp->start();
//        for(;!dsp->tic(););
//        dsp->stop("MSG");
    }
	std::cout<<"Kate stoped  \n";
};


