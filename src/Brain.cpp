//
// Created by Edouard on 29/11/2017.
//

#include "Brain.h"

Brain::Brain()
{
    _lastMoveX = 0;
    _lastMoveY = 0;
}

Brain::~Brain()
{

}

int Brain::calculateTurn(int x, int y)
{
    return (0);
}

int Brain::putFirstPiece()
{
    return (0);
}

int Brain::putBoardPiece(int x, int y, Board::TypeStone type)
{
    return (0);
}

int Brain::clear()
{
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