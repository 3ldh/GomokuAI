cmake_minimum_required(VERSION 3.6)
project(gomoku)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        src/Board.cpp
        src/Core.cpp src/Brain.cpp
        include/Communication.h src/main.cpp)

set(INCLUDE_FILES
        include/Core.h
        include/Board.h
        include/Brain.h
        src/Communication.cpp)

add_executable(pbrain-LookAtMyBigBrain ${SOURCE_FILES} ${INCLUDE_FILES})