cmake_minimum_required(VERSION 3.5)
project (Life VERSION 1.0.0 LANGUAGES CXX)


# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )
set (CMAKE_CXX_STANDARD 14)

#Include dir
include_directories(include)
 
add_executable(glife ../src/main.cpp)
