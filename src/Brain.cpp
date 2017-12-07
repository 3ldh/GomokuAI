//
// Created by Edouard on 29/11/2017.
//

#include <cstdlib>
#include "Brain.h"
#include <ctime>

Brain::Brain() : ai(AI())
{
    _lastMoveX = 0;
    _lastMoveY = 0;
    std::srand(static_cast<unsigned int>(std::time(0)));
}

Brain::~Brain()
{

}

Brain::BrainState Brain::calculateTurn(int x, int y)
{
    AI::Point p;

    ai.update_map('X', x, y);
    ai.update_score_map(x, y);
    p = ai.find_best_move();
    ai.update_map('O', p.x, p.y);
    ai.update_score_map(p.x, p.y);
    _lastMoveX = p.x;
    _lastMoveY = p.y;
    return (Brain::BrainEnd);
}

int Brain::putFirstPiece()
{
    std::unique_ptr<AI::Point> p = ai.first_move();
    _lastMoveX = p->x;
    _lastMoveY = p->y;
    ai.update_map('O', _lastMoveX, _lastMoveY);
    ai.update_score_map(_lastMoveX, _lastMoveY);
    return (0);
}

int Brain::putBoardPiece(int x, int y, Board::TypeStone type)
{
    if (type == Board::TheirStone)
        ai.update_map('X', x, y);
    else if (type == Board::OurStone)
        ai.update_map('O', x, y);
    ai.update_score_map(x, y);
    return (0);
}

int Brain::clear()
{
    ai = AI();
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