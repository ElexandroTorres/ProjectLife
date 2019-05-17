cmake_minimum_required(VERSION 3.5)
project (Life VERSION 1.0.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 14)

# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )


#Include dir
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
 
#add_executable(glife ../src/main.cpp, ../src/lodepng.cpp)

add_executable(glife ${SOURCES})
