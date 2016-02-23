project(bd)

set( HEADERS
    ${ROOT_DIR}/dispatcher/lib.h
    ai.h)

set( SOURCES
    ${ROOT_DIR}/dispatcher/lib.cpp
    ai.cpp)

add_library(ai SHARED
    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(ai)

message("       Module ai added ")

#obj/ai.o:
#	echo "building bd module"
#	mkdir -p obj
#	$(CC) $(CFLAGS) modules/bd/bd.cpp -o obj/bd.o