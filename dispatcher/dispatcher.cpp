/*! \brief Диспетчер запуска процессов.
 *  \autor Utop 
 *
 Имя:
    dispather.cpp
 Описание:
    !TODO Обязательно добавить сигналы и разультаты потоков.
 **/


#include "dispatcher.h"

// Именование библиотек + преффикс/суффикс
#include "platform.h"

dispatcher::dispatcher(inputString to_start)
{
    std::map<std::string, returnMod> mapFunction;
    std::vector<returnMes> vectMessages;
    std::list<std::string>::const_iterator i = to_start.begin();
    std::string str_tmp;

    returnMod modTmp;
    returnMes mesTmp;

    for(; i != to_start.end(); ++i) {
        str_tmp = *i;
        // Попытка найти данные о модулях
        modTmp = parserModules(str_tmp);
        if(modTmp.correct == 1) {
            mapFunction[modTmp.namemod] = returnMod(modTmp);
            std::cout << " string = " << str_tmp << "\n";

            // ! Важно инициализация списка, чтобы он не инициализировался при 
            //      обращении
            m_threads[modTmp.namemod] = nullptr;
        }
        // Попытка найти данные о сообщениях
        mesTmp = parserMessages(str_tmp);
        if(mesTmp.correct == 1) vectMessages.push_back(mesTmp);
    }

    // Проверка подключенных модулей
    for(auto itM = vectMessages.begin(); itM != vectMessages.end(); ++itM) {
        if((mapFunction[itM->frommod].correct == 1 || itM->frommod == "msg")&&
           mapFunction[itM->tomod].correct == 1) {
            //            if() msgertype * msgt = new msgertype();
            Messager * mess = new Messager(itM->nammes);
            mess->from = itM->frommod;
            mess->to = itM->tomod;
            // Принцып двойного связывания - по имени сообщения
            // от кого сообщение можно понять из Messager
            // Каждый модуль хранит только msgertype, а диспетчер - mapArgFunctions
            // std::map<std::string, Messager*> msgertype;
            // std::map<std::string, msgertype *> mapArgFunctions

            if(!m_argsToRun[mess->from]) {
                msgertype * msgt = new msgertype;
                m_argsToRun[mess->from] = msgt;
            }

            if(!m_argsToRun[mess->to]) {
                msgertype * msgt = new msgertype;
                m_argsToRun[mess->to] = msgt;
            }

            m_argsToRun[mess->from]->operator[]( itM->nammes ) = mess;
            m_argsToRun[mess->to]->operator[]( itM->nammes ) = mess;
            std::cout << "dispatcher:: message from module :" << mess->from << ": to module :" << mess->to << ": with name :" << itM->nammes << ": added\n";

        }
    }


    // Создание отдельного потока для месаджера
//     msgth;    
//typedef void (*start_function)(msgertype *);
    
//    typedef void (msg::* msgfun)(mapArgFunctions *);
//    typedef void (*msgfun)(mapArgFunctions *);
    //    void start(mapArgFunctions * messagelist);
//    msgfun msgst = &msg_start;
    void (* msgst)(mapArgFunctions *) = &(msg_start);
    std::thread * msgth = new std::thread(msgst,&m_argsToRun);
    msgth->detach();
    
    std::cout << " Num find Modules  = " << mapFunction.size() << "\n";
    // Заполнение списка потоков
    for(auto itT = mapFunction.begin(); itT != mapFunction.end(); ++itT) {
        if(itT->second.correct > 0) addThread(itT->second);
    }
};

int dispatcher::start()
{

    std::cout << " Dispatcher start \n";

    for(mapListsThreads::iterator listIterator = m_threads.begin()
        ; listIterator != m_threads.end(); ++listIterator) { // Запуск потоков

        if(listIterator->second != 0 && listIterator->second != nullptr) { // Есть список потоков

            std::cout << " Thread " << listIterator->first << " found ! \n";

            if(listIterator->second != nullptr) {
                for(thredList::iterator thredIterator = listIterator->second->begin();
                    thredIterator != listIterator->second->end(); ++thredIterator) {


                    std::thread* th_tmp;

                    th_tmp = thredIterator.operator*( );
                    //                    th_tmp->join();

                    std::cout << " Thread " << listIterator->first << " join, try Detach ! \n";

                    //                if(th_tmp->joinable())// && j->first != "mod:modules/inout")
                    {
                        th_tmp->detach(); // Отсоединение потока от главного
                    }
                }
            }
        }
    }


    for(auto tR = m_toRun.begin(); tR != m_toRun.end(); ++tR) { // Запуск модулей в главном потоке
        auto run_tmp = tR->second;
        std::cout << " Try to run    " << tR->first << "  runModule \n";
        ( *run_tmp )( m_argsToRun[tR->first] );
    };
    
    return 0;
};

int dispatcher::addThread(dispatcher::returnMod &mod)
{

    std::cout << "Try to open " << mod.namemod << " " << mod.path << " " << mod.number << " " << mod.correct << "\n";
    std::thread* runmodule = nullptr;

    //    std::string libname = "lib" + mod.namemod + ".a";
    std::string libname = platform::prefix + mod.namemod + platform::suffix;

    std::cout << "      Libname " << libname << "\n";

    if(mod.correct > 0) 
    {
        void * f = platform::OpenLibrary(libname);

        if(f == nullptr) return -1;
        std::cout << " Loaded library " << mod.namemod << " with name " << libname << "\n";

        start_function init_func = reinterpret_cast<start_function> ( f );


        if(init_func != nullptr && init_func != 0) {
            if(m_threads[mod.namemod] == nullptr) {
                m_threads[mod.namemod] = new thredList();
                std::cout << " New threadList with name " << mod.namemod << "  Created! \n";
            }

    // Если запуск происходит в отдельном потоке
            if(mod.number > 0) {
                for(int i = 0; i < mod.number; ++i) {
                    runmodule = new std::thread(init_func, m_argsToRun[mod.namemod]);
                    m_threads[mod.namemod]->push_back(runmodule); // Заполняем список потоков 
                }
                std::cout << "add :" << mod.namemod << ": X" << mod.number << "  times.  " << runmodule << "\n";
            }
            else {
                //typedef std::map<std::string, start_function> mapThreadFunctions;
                m_toRun[mod.namemod] = init_func;
                
            std::cout << " New module to run " << mod.namemod << "  Created! \n";
                
                // ! Функция на запуск! 
            }

            return 1;
        };

    }
    else {

    }

    return 0;
};

dispatcher::~dispatcher()
{
    // Закрытие всех библиотек
    platform::closeAll();

}; //dispatcher::~dispather()

dispatcher::returnMod dispatcher::parserModules(std::string inp)
{

    returnMod output;
    std::string minmask = "mod:\"m\":n";
    // Проверка на существование названия потока в строке
    if(inp.length() < minmask.length()) return output; // нет сообщения 
    int comment = inp.rfind('#'); // удаляем комментарии в конце
    std::string in = inp;
    if(comment >= 0) in.erase(comment, inp.size());

    std::string modmask = "mod:";
    std::string dirmask = "/";
    std::string colon = ":";
    std::string quote = "\"";
    //  # mod:directory_module/under_directory/"module_name":num_of_process 
    // поиск маски модуля ("mod:"), поиск кавычки, проверка на корректность пути 
    // (путь - строка между "mod:" и кавычкой), поиск второй кавычки,
    // выделение названия модуля, поиск двоеточия, считывание количества процессов

    int maskpos = in.find(modmask, 0);
    int index = maskpos;
    if(in[index] != 0 && index >= 0) {
        int firstcomma = in.find(quote, index);
        index = firstcomma + 1;
        int secondcomma = in.find(quote, index);
        index = secondcomma + 1;
        if(in[index] == 0) return output; // не нашли модуль

        // <- TODO проверка на корректность пути
        std::string path = "";
        for(int j = maskpos + modmask.size(); j < firstcomma - 1; ++j)
            path += in[j]; // Заполнили название пути


        // Обрезка имени файла
        std::string module = "";
        for(int j = firstcomma + 1; j < secondcomma; ++j)
            module += in[j]; // Заполнили название модуля

        int collonindex = in.find(colon, index); // Нашли двоеточие
        index = collonindex + 1;

        // Читаем количество запусков процесса
        std::string strnumber = "";
        while(std::isdigit(in[index])) {
            strnumber += in[index];
            ++index;
        }

        int number = std::stoi(strnumber);


        if(strnumber.length() <= 0 || number < 0) {
            return output;
        }; // Не нашли количество процессов

        output.namemod = module;
        output.number = number;
        output.path = path;
        output.correct = 1;

        std::cout << "find :" << module << ": x" << number << "  times. \n";

    }

    return output;
}; //     std::thread* dispatcher::parserModules(std::string in)

//int dispatcher::addMess(dispatcher::returnMes &mes)
//{
//
//    //    std::cout << "dispatcher::addMess => " << mes.frommod + "->" + mes.tomod + ":" + mes.nammes << "\" try \n";
//    //
//    //    if(modules[mes.frommod] && messager) {
//    //        if(modules[mes.tomod]) {
//    //            Messager* msg = new Messager(mes.nammes);
//    //            // Ужастно! указатель на map - последнее дело.
//    //            ( *modules[mes.frommod]->mp_messagelist )[mes.nammes] = msg;
//    //            ( *modules[mes.tomod]->mp_messagelist )[mes.nammes] = msg;
//    //            std::cout << "dispatcher::addMess message \"" << mes.frommod + "->" + mes.tomod + ":" + mes.nammes << "\" added \n";
//    //        }
//    //        else if(mes.tomod == "all") { // Групповая рассылка
//    //
//    //        }
//    //    } //         else if(mes.tomod == "inout"){
//    //        //            messager->pf_tic[mes.nammes] = inout::update; //reinterpret_cast<PFunction>(*inputoutput->tic);
//    //        ////             messager->pf_tic[mes.nammes] = modules[mes.tomod].tic;//inputoutput->update;
//    //        //                     //dynamic_cast<PFunction>((*inputoutput).update); //reinterpret_cast<PFunction>(*inputoutput->tic);
//    //        //         } // http://rsdn.ru/article/cpp/fastdelegate.xml
//    //    else {
//    //
//    //        std::cout << "dispatcher::addMess !!! message \"" << mes.frommod + "->" + mes.tomod + ":" + mes.nammes << "\" can\'t create \n";
//    //    };
//    // Потом будет вызываться:
//    //   module.messagelist["mesname"].put(message) в коде будет выглядить  messagelist["mesname"].put(message)
//    // и module.messagelist["mesname"].get(message)                         messagelist["mesname"].get(message)
//    // + module.messagelist["mesname"].isempty()                            messagelist["mesname"].isempty()
//    // + module.messagelist["mesname"].clear                                messagelist["mesname"].clear()
//    // 
//
//    return 0;
//}; // dispatcher::addMess(dispatcher::returnMes mes)

dispatcher::returnMes dispatcher::parserMessages(std::string inp)
{
    returnMes output;

    std::string minmask = "msg:\"f\"->\"t\":\"t\"";

    if(inp.length() < minmask.size()) return output; // нет сообщения 

    int comment = inp.rfind('#'); // удаляем комментарии в конце
    std::string in = inp;
    if(comment > 0) in.erase(comment, inp.size());
    int index = 0;

    std::string messmask = "msg:";
    std::string tomask = "->";
    std::string quote = "\"";
    std::string colon = ":";
    index = in.find(messmask, 0);
    if(in[index] != 0 && index >= 0) {
        // msg:"from"->"to":"type"
        // Находим маску, обрезаем ее, ищем первую кавычку,ищем вторую кавычку,
        // вырезаем имя первого модуля, ищем "->" ищем второй модуль, вырезаем имя
        // второго модуля, ищем двоеточие, ищем название
        int firstcomma = in.find(quote, index);
        index = firstcomma + 1;
        int secondcomma = in.find(quote, index);
        index = secondcomma + 1;
        if(in[index] == 0) return output; // не нашли первый модуль

        std::string frommodule = "";
        for(int j = firstcomma + 1; j < secondcomma; ++j)
            if(!std::isspace(in[j]))frommodule += in[j];
        // Заполнили название 1-го модуля
        int arrow = in.find(tomask, index);
        index = arrow + 1;
        firstcomma = in.find(quote, index);
        index = firstcomma + 1;

        secondcomma = in.find(quote, index);
        index = secondcomma + 1;
        if(in[index] == 0) return output; // не нашли второй модуль

        std::string tomodule = "";
        for(int j = firstcomma + 1; j < secondcomma; ++j)
            if(!std::isspace(in[j]))tomodule += in[j];
        // Заполнили название 2-го модуля

        int collonindex = in.find(colon, index); // Нашли двоеточие
        firstcomma = in.find(quote, collonindex + 1);
        index = firstcomma + 1;

        secondcomma = in.find(quote, index);
        if(secondcomma == -1 || in[secondcomma] == 0) return output; // не нашли название сообщения
        index = secondcomma + 1;

        std::string namemess = "";
        for(int j = firstcomma + 1; j < secondcomma; ++j)
            if(!std::isspace(in[j]))namemess += in[j];

        std::cout << "Find message from module :" << frommodule << ": to module :" << tomodule << ": with name :" << namemess << ":\n";

        output.frommod = frommodule;
        output.tomod = tomodule;
        output.nammes = namemess;
        output.correct = 1;
    } // if(in[index]!=0 && index >= 0)

    return output;

}; // void dispatcher::parserMessages(std::string in)





