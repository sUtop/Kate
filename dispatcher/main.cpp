#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

#include "dispatcher.h"

dispatcher::inputString to_start;

//char** argv;
//int argc;

int ReadConfig(std::string is = "") {
    std::string tmp = is;
    //    FILE fl;
    if (tmp == "") {
        tmp = "Kate.conf";
    };
    std::ifstream ConfigFile;
    ConfigFile.open(tmp);

    std::string line = "";
    if (ConfigFile) {
        while (getline(ConfigFile, line)) {
            if (!line.empty() && line[0] != '#') to_start.push_back(line);
            // Обработка конфигурационного файла. - происходит в диспетчере*/
        };
    };
    ConfigFile.close();

    return 1;
};

int main(int argc, char** argv) {
    //    mainargv = argv;
    //    mainargc = argc;

    std::cout << " Kate started with params :\"" << argc << "\"" << "\n";
    for (int i = 0; i < argc; ++i)
        std::cout << "=\"" << argv[i] << "\"\n";


    if (ReadConfig()) {
        dispatcher* dsp = new dispatcher(to_start);
        dsp->start();
    } else {
        std::cout << "Config not found!  \n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    
    std::cout << "Kate stoped  \n";
};


