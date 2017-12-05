//
// Created by Edouard on 29/11/2017.
//

#include <cstdlib>
#include "Brain.h"

//TODO remove time
#include <ctime>
Brain::Brain() : ai(AI())
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