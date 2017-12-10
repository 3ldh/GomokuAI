//
// Created by Edouard on 29/11/2017.
//

#include <cstdlib>
#include <ctime>
#include "Brain.h"

Brain::Brain() : ai(AI())
{
    firstPlayer = false;
    _lastMoveX = 0;
    _lastMoveY = 0;
    std::srand(static_cast<unsigned int>(std::time(0)));
    ai.setPlayerNb(2);
}

Brain::~Brain()
{

}

int Brain::calculateTurn(int x, int y)
{
    Point p;

//    ai.update_map('X', 9, 8);
//    ai.update_map('X', 9, 7);
//    ai.update_map('X', 9, 6);
//    ai.update_map('X', 9, 5);
//    ai.update_score_map(9, 6);
//    std::cout << "PLayerNB " << ai.getPlayerNb()<< " status " << ai.checkStatus() << std::endl;
    ai.setPlayerNb(2);
    ai.update_map('X', x, y);
    ai.update_score_map(x, y);

//     p = ai.find_best_move();
//    std::cout << p << std::endl;

    p = monteCarlo.findNextMove(ai, 2);
//    std::cout << p << std::endl;
    ai.update_map('O', p.x, p.y);
    ai.update_score_map(p.x, p.y);
    ai.printMap();
    ai.print_score_map();
    _lastMoveX = p.x;
    _lastMoveY = p.y;
    return (0);
}

int Brain::putFirstPiece()
{
    firstPlayer = true;
    std::unique_ptr<Point> p = ai.first_move();

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

unsigned int Brain::getLastMoveX() const
{
    return (this->_lastMoveX);
}

unsigned int Brain::getLastMoveY() const
{
    return (this->_lastMoveY);
}

void Brain::signalEnd()
{
    ai.signalEnd();
}