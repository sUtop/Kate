project(phz)

set( HEADERS
    ${ROOT_DIR}/dispatcher/lib.h
    phz.h)

set( SOURCES
    ${ROOT_DIR}/dispatcher/lib.cpp
    phz.cpp)

add_library(phz SHARED
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(phz)


message("       Module phz added ")
