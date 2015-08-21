#include "dispatcher.h"

//dispatcher::dispatcher(int argc,char** argv){
//        
//};

dispatcher::dispatcher(inputString to_start){
    std::list<std::string>::const_iterator i = to_start.begin();
    std::string str_tmp; 
//    std::thread* th_tmp;
    returnMod mod_tmp;
    returnMes mes_tmp;
    for(;i!=to_start.end();i++)
    {
        str_tmp = *i;
        mod_tmp = parserModules(str_tmp);
        if(mod_tmp.correct == 1) addThread(mod_tmp);
        mes_tmp = parserMessages(str_tmp);
        if(mes_tmp.correct == 1) addMess(mes_tmp);
    }
};

int dispatcher::start(){

    PFunction run_tmp;
    
    std::map<std::string,PFunction>::iterator k = torun.begin();
    for(;k!=torun.end();k++){   // Запуск модулей в главном потоке
        run_tmp = k->second;
        (*run_tmp)();
    };

    std::thread* th_tmp;
    mapListsThreads::iterator listIterator = threads.begin();
    for(;listIterator!=threads.end();listIterator++){ // Запуск потоков
        thredList::iterator thredIterator = listIterator->second.begin();
//        thredList::iterator thredIterator = 
        for(;thredIterator!=listIterator->second.end();thredIterator++){
            th_tmp = thredIterator.operator *();
            th_tmp->join();
            if(th_tmp->joinable())// && j->first != "mod:modules/inout")
            {
                th_tmp->detach();   // Отсоединение потока от главного
            }
        }
    }
    
    return 0;
};

int dispatcher::stop(std::string proc){
//    if(threads[proc]) {threads[proc]->~thread(); return 0;}  // TODO ! плохой - не освобождает память !?
    return 1;
};

int dispatcher::stop(){
//    std::map<std::string,std::thread*>::iterator j = threads.begin();
//    for(;j!=threads.end();j++){
//        stop(j->first);
//    };
    return 0;
    
};

int dispatcher::tic(){
//  if(error) return 1;
    return 0;
};


int dispatcher::addThread(dispatcher::returnMod mod){

    std::thread* runmodule = 0;
    if(mod.namemod == "msg") {
            runmodule = new std::thread(msg::start);
            modules[mod.namemod]=messager;
        }//reinterpret_cast
        else if(mod.namemod == "bd") {
            runmodule = new std::thread(bd::start);
            modules[mod.namemod]=database;
        }
        else if(mod.namemod == "inout") {
            std::cout<<mod.namemod<<"inout to run \n";
            torun[mod.namemod] = inout::start_main;
            runmodule = new std::thread(inout::start);
            modules[mod.namemod]=inputoutput;
        }
        else if(mod.namemod == "phz") {
            runmodule = new std::thread(phz::start);
            modules[mod.namemod]=physics;
        }
    
    if(runmodule){
        for(int i=0;i<mod.number;i++)threads[mod.namemod].push_back(runmodule); // Заполняем список потоков 
//    std::cout<<"add :"<<mod.namemod<<": X"<<mod.number<<"  times. \n";
        return 1;
    };
    return 0;
};



dispatcher::returnMod dispatcher::parserModules(std::string inp){
    
    returnMod output = {"","",0,-1};
    std::string minmask = "mod:\"m\":n";
    // Проверка на существование названия потока в строке
    if(inp.length() < minmask.length()) return output; // нет сообщения 
    int comment = inp.rfind('#'); // удаляем комментарии в конце
    std::string in = inp;
    if(comment>=0) in.erase(comment,inp.size());

    std::string modmask = "mod:";
    std::string dirmask = "/";
    std::string colon = ":";
    std::string quote = "\"";
    //  # mod:directory_module/under_directory/"module_name":num_of_process 
    // поиск маски модуля ("mod:"), поиск кавычки, проверка на корректность пути 
    // (путь - строка между "mod:" и кавычкой), поиск второй кавычки,
    // выделение названия модуля, поиск двоеточия, считывание количества процессов

    int maskpos = in.find(modmask,0);
    int index = maskpos;
    if(in[index]!=0 && index >= 0){
        int firstcomma = in.find(quote,index);
        index = firstcomma + 1;
        int secondcomma = in.find(quote,index);
        index = secondcomma + 1;
        if(in[index]==0) return output; // не нашли модуль
        
        // <- TODO проверка на корректность пути
        std::string path = "";
        for(int j=maskpos+modmask.size();j<firstcomma-1;++j)
            path += in[j]; // Заполнили название пути
        
        
        std::string module = "";
        for(int j=firstcomma+1;j<secondcomma;++j)
            module += in[j]; // Заполнили название модуля
        
        int collonindex=in.find(colon,index); // Нашли двоеточие
        index = collonindex + 1;
        
        std::string strnumber = "";
        while(std::isdigit(in[index])){
            strnumber += in[index];
            index++;
        }
        
        int number = std::stoi(strnumber);
        

        if( strnumber.length()<=0 || number < 0){ return output; }; // Не нашли количество процессов
            
        output.namemod = module;
        output.number = number;
        output.path = path;
        output.correct = 1;

        std::cout<<"find :"<<module<<": x"<<number<<"  times. \n";
        
    }

    return output;
}; //     std::thread* dispatcher::parserModules(std::string in)


int dispatcher::addMess(dispatcher::returnMes mes){
    
    std::cout<<"dispatcher::addMess => "<<mes.frommod + "->" + mes.tomod + ":" + mes.nammes<<"\" try \n";

    if(modules[mes.frommod] && messager){
     if(modules[mes.tomod]){
        Messager* msg = new Messager(mes.nammes);
        modules[mes.frommod]->messagelist[mes.nammes] = msg;
        modules[mes.tomod]->messagelist[mes.nammes] = msg;
        std::cout<<"dispatcher::addMess message \""<<mes.frommod + "->" + mes.tomod + ":" + mes.nammes<<"\" added \n";
     }else if (mes.tomod == "all"){ // Групповая рассылка

     }
     }
//         else if(mes.tomod == "inout"){
//            messager->pf_tic[mes.nammes] = inout::update; //reinterpret_cast<PFunction>(*inputoutput->tic);
////             messager->pf_tic[mes.nammes] = modules[mes.tomod].tic;//inputoutput->update;
//                     //dynamic_cast<PFunction>((*inputoutput).update); //reinterpret_cast<PFunction>(*inputoutput->tic);
//         } // http://rsdn.ru/article/cpp/fastdelegate.xml
     else{

        std::cout<<"dispatcher::addMess !!! message \""<<mes.frommod + "->" + mes.tomod + ":" + mes.nammes<<"\" can\'t create \n";                 
     };
    // Потом будет вызываться:
    //   module.messagelist["mesname"].put(message) в коде будет выглядить  messagelist["mesname"].put(message)
    // и module.messagelist["mesname"].get(message)                         messagelist["mesname"].get(message)
    // + module.messagelist["mesname"].isempty()                            messagelist["mesname"].isempty()
    // + module.messagelist["mesname"].clear                                messagelist["mesname"].clear()
    // 

    return 0;
}; // dispatcher::addMess(dispatcher::returnMes mes)

dispatcher::returnMes dispatcher::parserMessages(std::string inp){
    returnMes output = {"","","",-1};
    
    std::string minmask = "msg:\"f\"->\"t\":\"t\"";
    
    if(inp.length() < minmask.size()) return output; // нет сообщения 
    
    int comment = inp.rfind('#'); // удаляем комментарии в конце
    std::string in = inp;
    if(comment>0) in.erase(comment,inp.size());
    int index = 0;

    std::string messmask = "msg:";
    std::string tomask = "->";
    std::string quote = "\"";
    std::string colon = ":";
    index = in.find(messmask,0);
    if(in[index]!=0 && index >= 0){
        // msg:"from"->"to":"type"
        // Находим маску, обрезаем ее, ищем первую кавычку,ищем вторую кавычку,
        // вырезаем имя первого модуля, ищем "->" ищем второй модуль, вырезаем имя
        // второго модуля, ищем двоеточие, ищем название
        int firstcomma = in.find(quote,index);
        index = firstcomma+1;
        int secondcomma = in.find(quote,index);
        index = secondcomma+1;
        if(in[index]==0) return output; // не нашли первый модуль

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
        if(in[index]==0) return output; // не нашли второй модуль

        std::string tomodule = "";
        for(int j=firstcomma+1;j<secondcomma;++j)
            if(!std::isspace(in[j]))tomodule += in[j];
                                                        // Заполнили название 2-го модуля

        int collonindex=in.find(colon,index);                     // Нашли двоеточие
        firstcomma = in.find(quote,collonindex+1);
        index = firstcomma+1;

        secondcomma = in.find(quote,index);
        if(secondcomma==-1 || in[secondcomma]==0) return output; // не нашли название сообщения
        index = secondcomma+1;

        std::string namemess = "";
        for(int j=firstcomma+1;j<secondcomma;++j)
            if(!std::isspace(in[j]))namemess += in[j];

        std::cout<<"Find message from module :"<<frommodule<<": to module :"<<tomodule<<": with name :"<<namemess<<":\n";

        output.frommod = frommodule;
        output.tomod = tomodule;
        output.nammes = namemess;
        output.correct = 1;
    } // if(in[index]!=0 && index >= 0)

    return output;

}; // void dispatcher::parserMessages(std::string in)




