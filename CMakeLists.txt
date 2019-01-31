#project name
project(dictionaryConverter)

#cmake minimum version
cmake_minimum_required(VERSION 2.8)

#compiler
set(CMAKE_C_COMPILER "gcc")

#binary name
set(BIN_NAME ditionaryConverter.exe)

#source list
set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/dictionaryConverter.c
)

#include files
include_directories(BIN_NAME
#	${CMAKE_SOURCE_DIR}/include
)

#make executable file
add_executable(${BIN_NAME} ${SRC_LIST})
