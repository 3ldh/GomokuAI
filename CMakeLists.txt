cmake_minimum_required(VERSION 3.6)
project(gomoku)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        src/Board.cpp
        src/Core.cpp src/Brain.cpp
        include/Communication.h src/main.cpp
        src/main.cpp
        src/AI.cpp
        src/Tree.cpp
        src/Node.cpp
        src/State.cpp
        src/UCT.cpp
        src/MonteCarlo.cpp
        src/Timer.cpp)

set(INCLUDE_FILES
        include/Core.h
        include/Board.h
        include/Brain.h
        src/Communication.cpp
        include/AI.h
        include/Tree.h
        include/Node.h
        include/State.h
        include/MonteCarlo.h
        include/Point.h
        include/UCT.h
        include/Timer.h)

add_executable(pbrain-LookAtMyBigBrain ${SOURCE_FILES} ${INCLUDE_FILES})