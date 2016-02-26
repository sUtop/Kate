/* 
 * File:   gnu/platform.h
 * Author: Utop
 * \brief Модуль системнозависимых параметров для MacOs
 * Created on 24 Февраль 2016 г., 15:51
 */

#ifndef PLATFORM_H
#define	PLATFORM_H

namespace platform {
#include <string>
#include <dlfcn.h> // ! dlopen и подобные
    //    #include <dlsym.h>
    const std::string prefix = "./lib"; // Указание директории обязательно! (./)
    const std::string suffix = ".so";

#include <map> 

    static std::map<std::string, void *> LoadedLibrary;
    //!< Список уже загруженных библиотек с хэндлами

    void * OpenLibrary(std::string libname) {

        if (LoadedLibrary[libname] == nullptr) {
            void * handle = dlopen(libname.c_str(), RTLD_LAZY);
            std::cout << " dlopen " << libname << " opened with code " << handle << " \n";
            if (!handle) return nullptr;
            LoadedLibrary[libname] = handle;
        } else std::cout << " Ha ! I found your lib - " << libname << " it is on " << LoadedLibrary[libname] << "\n";
        

        void * f = dlsym(LoadedLibrary[libname], "start");
        std::cout << " dlsym " << "start" << " opened with code " << f << " \n";
        return f;
    }


}



#endif	/* PLATFORM_H */

