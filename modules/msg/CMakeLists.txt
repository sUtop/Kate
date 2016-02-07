project(msg)

set( HEADERS
    msg.h)

set( SOURCES
    msg.cpp)

add_library(msg
#    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(msg)