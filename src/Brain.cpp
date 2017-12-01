//
// Created by Edouard on 29/11/2017.
//

#include <cstdlib>
#include "Brain.h"

//TODO remove time
#include <ctime>
Brain::Brain()
{
    _lastMoveX = 0;
    _lastMoveY = 0;
    //TODO remove the random
    std::srand(std::time(0));
    _board.clear();
}

Brain::~Brain()
{

}

//TODO remove the random
#include <iostream>
int Brain::calculateTurn(int x, int y)
{
    int xT = 10;
    int yT = 10;

    _board._board[xT][yT] = Board::TheirStone;
    while (_board._board[xT][yT] != Board::EmptyStone)
    {
        xT = rand() % 19;
        yT = rand() % 19;
    }
    _lastMoveX = xT;
    _lastMoveY = yT;
    _board._board[xT][yT] = Board::OurStone;
    return (0);
}

//TODO remove the random
int Brain::putFirstPiece()
{
    _lastMoveX = 10;
    _lastMoveY = 10;
    _board._board[10][10] = Board::OurStone;
    return (0);
}

int Brain::putBoardPiece(int x, int y, Board::TypeStone type)
{
    //TODO remove the random
    _board._board[x][y] = type;
    return (0);
}

int Brain::clear()
{
    //TODO remove the random
    _board.clear();
    return (0);
}

int Brain::getLastMoveX() const
{
    return (this->_lastMoveX);
}
int Brain::getLastMoveY() const
{
    return (this->_lastMoveY);
}