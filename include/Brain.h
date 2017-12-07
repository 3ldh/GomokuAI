//
// Created by Edouard on 29/11/2017.
//

#ifndef GOMOKU_BRAIN_H
#define GOMOKU_BRAIN_H

#include "Board.h"
#include "AI.h"


class Brain{
public:
private:
    unsigned int _lastMoveX;
    unsigned int _lastMoveY;
    AI ai;

public:
    Brain();
    ~Brain();
    int calculateTurn(int x, int y);
    int putFirstPiece();
    int putBoardPiece(int x, int y, Board::TypeStone type);
    unsigned int getLastMoveX() const;
    unsigned int getLastMoveY() const;
    int clear();
    void signalEnd();
};

#endif //GOMOKU_BRAIN_H
