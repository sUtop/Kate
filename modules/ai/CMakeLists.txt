project(bd)

set( HEADERS
    ai.h)

set( SOURCES
    ai.cpp)

add_library(ai
    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(ai)

message("       Module ai added ")

#obj/ai.o:
#	echo "building bd module"
#	mkdir -p obj
#	$(CC) $(CFLAGS) modules/bd/bd.cpp -o obj/bd.o