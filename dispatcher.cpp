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
        th_tmp = parserModules(str_tmp);
        if(th_tmp){
         threads[str_tmp] = th_tmp; // Заполняем список потоков 
         
         
        }
        parserMessages(str_tmp);
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
    if(threads[proc]) {threads[proc]->~thread(); return 0;}  // TODO ! плохой - не освобождает память !?
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


    std::thread* dispatcher::parserModules(std::string in){
        int iter=0; // Защита от зацыкливания
        // Проверка на существование названия потока в строке
        if(in.length() < 3) return 0;
        int index = 0;
        std::thread* output = 0;
        std::string modmask = "mod:";
        std::string dirmask = "/";
        
        // Поиск по маске модуля
        index = in.find(modmask,0);
//        std::cout<<"index = "<<index<<"\n";
        while(in[index]!=0 || index >= 0){
            iter++;
            if(in[index] == '#') return 0; // Комментарий
            // Находим маску, обрезаем ее, обрезаем путь до модуля, возвращаем
            // если не нашли маску - возвращаем нуль
            int i=in.find(dirmask,index);
            
            if(i<in.length()) index = i+1;
            else {
                std::string nameModule = "";
                for(int j=index;j<in.length();++j)
                    if(!std::isspace(in[j]))nameModule += in[j];
                std::cout<<"Catched name module :"<<nameModule<<":\n";
                if(nameModule == "msg") {
                    output = new std::thread(msg::start);
                    modules[nameModule]=dynamic_cast<module*>(messager);
                }//reinterpret_cast
                    else if(nameModule == "bd") {
                    output = new std::thread(bd::start);
                    modules[nameModule]=dynamic_cast<module*>(database);}
                    else if(nameModule == "inout") {
                    output = new std::thread(inout::start);
                    modules[nameModule]=dynamic_cast<module*>(inputoutput);
                    }
                    else if(nameModule == "phz") {
                    output = new std::thread(phz::start);
                    modules[nameModule]=dynamic_cast<module*>(physics);
                    }
                return output;
            }
            if(std::isspace(in[index])) {index++; /*continue;*/}
            if(iter>100) return 0;
        }
        return 0;
    }; //     std::thread* dispatcher::parserModules(std::string in)

    
void dispatcher::parserMessages(std::string in){
        if(in.length() < 3) return;
        int index = 0;
        
        std::string messmask = "msg:";
        std::string tomask = "->";
        std::string quote = "\"";
        std::string colon = ":";
        index = in.find(messmask,0);
        if(in[index]!=0 || index >= 0){
            if(in[index] == '#') return; // Комментарий
            // msg:"from"->"to":"type"
            // Находим маску, обрезаем ее, ищем первую кавычку,ищем вторую кавычку,
            // вырезаем имя первого модуля, ищем "->" ищем второй модуль, вырезаем имя
            // второго модуля, ищем двоеточие, ищем название
            int firstcomma = in.find(quote,index);
            index = firstcomma+1;
            int secondcomma = in.find(quote,index);
            index = secondcomma+1;
            if(in[index]==0) return; // не нашли первый модуль
            
            std::string frommodule = "";
            for(int j=firstcomma+1;j<secondcomma;++j)
                if(!std::isspace(in[j]))frommodule += in[j];
                                                            // Заполнили название 1-го модуля
            int arrow = in.find(tomask,index);
            index = arrow+1;
            firstcomma = in.find(quote,index);
            index = firstcomma+1;

            secondcomma = in.find(quote,index);
            index = secondcomma+1;
            if(in[index]==0) return; // не нашли второй модуль
            
            std::string tomodule = "";
            for(int j=firstcomma+1;j<secondcomma;++j)
                if(!std::isspace(in[j]))tomodule += in[j];
                                                            // Заполнили название 2-го модуля
            
            int collonindex=in.find(colon,index);                     // Нашли двоеточие
            firstcomma = in.find(quote,collonindex+1);
            index = firstcomma+1;

            secondcomma = in.find(quote,index);
            if(secondcomma==-1 || in[secondcomma]==0) return; // не нашли название сообщения
            index = secondcomma+1;
            
            std::string namemess = "";
            for(int j=firstcomma+1;j<secondcomma;++j)
                if(!std::isspace(in[j]))namemess += in[j];
            
            std::cout<<"Find message from module :"<<frommodule<<": to module :"<<tomodule<<": with name :"<<namemess<<":\n";
            
            // messager.addmessagelist(modules[frommodule].put,modules[tomodule].get,namemess);
            // или
            // messager.addmessage(modules[frommodule].put,namemess)
            // messager.resivemessage(modules[tomodule].get,namemess)
            // или 
            
             Messager* msg = new Messager(namemess);
             std::cout<<"Msg create \n";
             modules[frommodule]->messagelist[namemess] = msg;
             modules[tomodule]->messagelist[namemess] = msg;
             messager->messagelist[frommodule + "->"+ tomodule + ":" + namemess] = msg;

             std::cout<<"message \""<<frommodule + "->" + tomodule + ":" + namemess<<"\" added \n";
             
            // Потом будет вызываться:
            //   module.messagelist["mesname"].put(message) в коде будет выглядить  messagelist["mesname"].put(message)
            // и module.messagelist["mesname"].get(message)                         messagelist["mesname"].get(message)
            // + module.messagelist["mesname"].isempty()                            messagelist["mesname"].isempty()
            // + module.messagelist["mesname"].clear                                messagelist["mesname"].clear()
            // 
            //    msgertype* msg = new msgertype("tic") ??? или msg = messager.tic
            //    std::map<std::string,std::thread*>::iterator j = threads.begin();
            //    for(;j!=threads.end();j++){
            //        j->messagelist["tic"] = msg;
            
//            modules[frommodule]->openLogFile();
            
            
        }

        return;
            
}; // void dispatcher::parserMessages(std::string in)

    


