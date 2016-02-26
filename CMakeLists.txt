# Головной CMake-файл
#
cmake_minimum_required(VERSION 3.0.0)

#  Имя проекта
project(Kate)

# Текущая версия
set(VERSION "0.0.5")

# Путь до корневой директории
set (ROOT_DIR ${PROJECT_SOURCE_DIR})

message("~~~Building  ${PROJECT_SOURCE_DIR}\n~~~project-name:${PROJECT_NAME}")

# Установка путей, используемых во время сборки (для конечного результата):
set (CMAKE_BINARY_DIR ${ROOT_DIR}/bin)
# Для хранения временных файлов:
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



if (EXISTS "bin")
   file(REMOVE_RECURSE "bin")
endif()


string(TOUPPER ${CMAKE_SYSTEM} U_SYSTEM)

if (${U_SYSTEM} MATCHES "DARWIN")

	set(U_PLATFORM MAC)
        # Установка стандарта с++14 и добавления отладочной информации
        add_definitions(-std=c++14 -g)
        # ldl - подключение dlfcn.h - библиотеки для динамического подключения библиотек
        # lpthread - подключение библиотеки потоков
        # fPIC - динамическое связывание
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -fPIC")

        message("!!! Hi! Your system is Mac! ")
elseif (${U_SYSTEM} MATCHES "LINUX")

	set(U_PLATFORM LINUX)
        # Установка стандарта с++14 и добавления отладочной информации
        add_definitions(-std=c++14 -g)
        # ldl - подключение dlfcn.h - библиотеки для динамического подключения библиотек
        # lpthread - подключение библиотеки потоков
        # fPIC - динамическое связывание
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread -fPIC")

        message("!!! Hi, GNU user! ")

elseif (${U_SYSTEM} MATCHES "SUNOS")
	set(U_PLATFORM SUNOS)
        set(INCLUDEDIR "no_matches")

elseif (${U_SYSTEM} MATCHES "WINDOWS")
	set(U_PLATFORM WIN)

# Проверка на вижуалку - 14

endif (${U_SYSTEM} MATCHES "DARWIN")




# Установка заголовков основного модуля - диспетчера + мессаджера
set( SOURCES
    ${ROOT_DIR}/dispatcher/dispatcher.cpp
    ${ROOT_DIR}/dispatcher/lib.cpp
    ${ROOT_DIR}/dispatcher/msg/msg.cpp
    ${ROOT_DIR}/dispatcher/main.cpp
)

# Подключение заголовков основного модуля 
include_directories("dispatcher")
include_directories("dispatcher/msg")

# Сохранение путей до главных заголовков
set( PUBLIC
    ${ROOT_DIR}/dispatcher/dispatcher.h
    ${ROOT_DIR}/dispatcher/lib.h
    ${ROOT_DIR}/dispatcher/msg/msg.h
)

# Копирование конфигурационного файла
file(COPY "other/Kate.conf" DESTINATION "bin")
#file(COPY "dispatcher/lib.h" DESTINATION "bin")

# Добавление модулей в сборку
add_subdirectory(modules)

add_executable(Kate ${SOURCES} ) 
# ${PUBLIC} 

#add_dependencies(Kate modules)

