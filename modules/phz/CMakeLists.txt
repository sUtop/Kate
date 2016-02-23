project(phz)

set( HEADERS
    phz.h)

set( SOURCES
    phz.cpp)

add_library(phz
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(phz)


message("       Module phz added ")
