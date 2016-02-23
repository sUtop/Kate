/* 
 * File:   platform.h
 * Author: Utop
 * \brief Модуль системнозависимых параметров для MacOs
 * Created on 24 Февраль 2016 г., 15:51
 */

#ifndef PLATFORM_H
#define	PLATFORM_H

namespace platform {
    #include <string>
    #include <dlfcn.h> // ! dlopen и подобные

    const std::string prefix = "lib";
    const std::string suffix = ".dlyb";
    
    void * OpenLibrary(std::string libname) {
        void * handle = dlopen(libname.c_str(), RTLD_LAZY);
        return dlsym(handle, "start");
    }
    
    
}


#endif	/* PLATFORM_H */

