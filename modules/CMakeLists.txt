
project(modules)

# Поиск всех CMake-файлов в поддиректориях
file(GLOB modules ${CMAKE_CURRENT_SOURCE_DIR} "*/CMakeLists.txt")

# обход поддиректорий
foreach(dir ${modules})    
    if(${dir} MATCHES "^(.*)/CMakeLists.txt")
        # Имена поддиректорий
        string(REGEX REPLACE "^(.*)/CMakeLists.txt" "\\1" dir_trimmed ${dir})
        # Имена модулей
        string(REGEX REPLACE "^(.*)/([^/]*$)" "\\2" name_module ${dir_trimmed})
        # Вывод сообщения
        message("~~~ Found module \"${name_module}\" try add it")
        # Добавление поддиректорий
        add_subdirectory(${dir_trimmed})
    endif()
endforeach(dir)


