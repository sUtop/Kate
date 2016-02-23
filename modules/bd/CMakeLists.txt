project(bd)

set( HEADERS
    ${ROOT_DIR}/dispatcher/lib.h
    bd.h)

set( SOURCES
    ${ROOT_DIR}/dispatcher/lib.cpp
    bd.cpp)

add_library(bd SHARED
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(bd)

message("       Module bd added ")
