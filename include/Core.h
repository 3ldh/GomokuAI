//
// Created by Edouard on 29/11/2017.
//

#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include "Board.h"
#include "Brain.h"
#include "Communication.h"

class Core{
private:
    struct Position{
        Position (int xval = 0, int yval = 0){
            x = xval;
            y = yval;
        }
        int x;
        int y;
    };

    enum commandRead {
        CmdStart = 0,
        CmdTurn,
        CmdBegin,
        CmdBoard,
        CmdInfo,
        CmdEnd,
        CmdAbout,
        NbCommandRead
    };

    enum stateGame {
        StateLaunch,
        StateStart,
        StateInGame,
        StateBoard,
        StateEnd
    };

    typedef int (Core::*fctProceed)(std::stringstream &);

    Board                   _board;
    Brain                   _brain;
    Communication           _com;
    std::string             _readCmd[NbCommandRead];
    fctProceed              _readFctArray[NbCommandRead];
    stateGame               _state;
    Position                _lastBoard;
	std::mutex				_mutex;
    std::queue<Position>    _queue;
    std::condition_variable _cond;

    int proceedStart(std::stringstream &inputStream);
    int proceedTurn(std::stringstream &inputStream);
    int proceedBegin(std::stringstream &inputStream);
    int proceedBoard(std::stringstream &inputStream);
    int proceedDone();
    int proceedInfo(std::stringstream &inputStream);
    int proceedEnd(std::stringstream &inputStream);
    int proceedAbout(std::stringstream &inputStream);
    int readAndProceedCommand();
    int proceedThreadTurn(int x, int y);
    int runAndProceedTurn();

public:
    Core();
    ~Core();
    int run();
};

#endif /* !GOMOKU_CORE_H */
