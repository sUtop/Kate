// XP
#include <bitset>
#include <iostream>

#include "dispatcher.h"

dispatcher::dispatcher(int argc,char** argv){
        
};

dispatcher::dispatcher(std::list<std::string> to_start){
    std::list<std::string>::const_iterator i = to_start.begin();
    std::string str_tmp; 
    std::thread* th_tmp;
    for(;i!=to_start.end();i++)
    {
        str_tmp = *i;
        th_tmp = parser(str_tmp);
        if(th_tmp){
         threads[str_tmp] = th_tmp; // Заполняем список потоков 
        }
    }

};

int dispatcher::start(){
    std::thread* th_tmp;
    std::map<std::string,std::thread*>::iterator j = threads.begin();
    for(;j!=threads.end();j++){
        th_tmp = j->second;
        th_tmp->join();            // Запуск потока
        if(th_tmp->joinable())th_tmp->detach();
    }
    return 0;
};

int dispatcher::stop(std::string proc){
    if(threads[proc]) {threads[proc]->~thread(); return 0;}  // TODO ! плохой - не освобождает память!
    return 1;
};

int dispatcher::stop(){
    std::map<std::string,std::thread*>::iterator j = threads.begin();
    for(;j!=threads.end();j++){
        stop(j->first);
    };
    return 0;
    
};

int dispatcher::tic(){

    
//  if(error) return 1;

    return 0;
};


    std::thread* dispatcher::parser(std::string in){
        // Проверка на существование потока
        
//        if(std::count(tmp)>0){
//            int num = std::find(tmp.begin(),tmp.end(),std::string);
//            std::cout<<"--"<<num<<'\n';
//            std::string::iterator j = tmp.begin();
//        }
//        std::cout<<":"<<*i<<":"<<"\n";
        std::thread* output = 0;
        
        int folderIndex=0;
//        std::string::iterator pstr = in.begin();
        for(int i=0;i<in.length();i++)
            if(in[i] == '/') folderIndex = i;
        if(folderIndex>0 && folderIndex < in.length()){
            std::string nameModule = "";
            for(int i=folderIndex+1;i<in.length();++i)
                nameModule += in[i];
            std::cout<<"Catched :"<<nameModule<<":\n";
            
            if(nameModule == "msg") output = new std::thread(msg::start);
            if(nameModule == "bd") output = new std::thread(bd::start);
            if(nameModule == "inp") output = new std::thread(inp::start);
            if(nameModule == "out") output = new std::thread(out::start);
            if(nameModule == "phz") output = new std::thread(phz::start);
            return output;
        }
        
        
        
        std::cout<<"thread :"<<in<<": not created!\n";
        return 0;
    };



