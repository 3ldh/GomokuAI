cmake_minimum_required(VERSION 3.6)   # CMake version check
project(gomoku)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++11 standard

include_directories(include)

set(SOURCE_FILES
#        src/example.cpp
#        src/pisqpipe.cpp
        src/main.cpp
        src/IA.cpp)            # Add main.cpp file of project root directory as source file

set(INCLUDE_FILES
#        include/pisqpipe.h
        include/IA.h)

add_executable(gomoku ${SOURCE_FILES} ${INCLUDE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable