project(bd)

set( HEADERS
    bd.h)

set( SOURCES
    bd.cpp)

add_library(bd
    ${PUBLIC}
    ${SOURCES} 
    ${HEADERS})

target_link_libraries(bd)

obj/bd.o:
	echo "building bd module"
	mkdir -p obj
	$(CC) $(CFLAGS) modules/bd/bd.cpp -o obj/bd.o