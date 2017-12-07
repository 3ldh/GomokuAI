//
// Created by Edouard on 29/11/2017.
//

#include <cstdlib>
#include "Brain.h"
#include <ctime>
#include <unistd.h>

Brain::Brain() : ai(AI())
{
    _lastMoveX = 0;
    _lastMoveY = 0;
    std::srand(std::time(0));
    _board.clear();
}

Brain::~Brain()
{

}

//TODO remove sleep
#include <afxres.h>

int Brain::calculateTurn(int x, int y)
{
    AI::Point p;

    ai.update_map('X', x, y);
    ai.update_score_map(x, y);
    p = ai.find_best_move();
    ai.update_map('O', p.x, p.y);
    ai.update_score_map(p.x, p.y);
    _lastMoveX = p.x;
    _lastMoveY = p.y;
    _board._board[p.x][p.y] = Board::OurStone;
    Sleep(2000);
    return (0);
}

//TODO remove the random
int Brain::putFirstPiece()
{
    std::unique_ptr<AI::Point> p = ai.first_move();
    _lastMoveX = p->x;
    _lastMoveY = p->y;
    ai.update_map('O', _lastMoveX, _lastMoveY);
    ai.update_score_map(_lastMoveX, _lastMoveY);
    _board._board[_lastMoveX][_lastMoveY] = Board::OurStone;
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
    ai = AI();
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