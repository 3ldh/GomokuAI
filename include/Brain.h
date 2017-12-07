//
// Created by Edouard on 29/11/2017.
//

#ifndef GOMOKU_BRAIN_H
#define GOMOKU_BRAIN_H

#include "Board.h"
#include "AI.h"


class Brain{
public:
    enum BrainState {
        BrainContinue = 0,
        BrainEnd,
        BrainError,
    };
private:
    int _lastMoveX;
    int _lastMoveY;
    AI ai;

public:
    Brain();
    ~Brain();
    BrainState calculateTurn(int x, int y);
    int putFirstPiece();
    int putBoardPiece(int x, int y, Board::TypeStone type);
    int getLastMoveX() const;
    int getLastMoveY() const;
    int clear();
};

#endif //GOMOKU_BRAIN_H
