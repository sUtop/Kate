cmake_minimum_required(VERSION 2.4.4)

project(Kate)

set(VERSION "0.0.1")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


set(ROOT_DIR ${PWD})

set( SOURCES
    ${ROOT_DIR}/src/dispatcher.cpp
    ${ROOT_DIR}/src/main.cpp)


include_directories(include)
set( PUBLIC
    ${ROOT_DIR}/include/dispatcher.h
    ${ROOT_DIR}/include/lib.h)



add_subdirectory(modules)

add_executable(Kate ${SOURCES})

add_dependencies(Kate modules)


