//
// Created by Mathieu on 07/12/2017.
//

#ifndef GOMOKU_MONTECARLO_H
#define GOMOKU_MONTECARLO_H


#include "AI.h"
#include "Node.h"

class MonteCarlo {
private :
    static const int WIN_SCORE = 10;
    int opponent;
    long getCurrentTime();
    void expandNode(const std::shared_ptr<Node> &node);
    const std::shared_ptr<Node> findNextBestNode(const std::shared_ptr<Node> &node);
    int simulatePlay(const std::shared_ptr<Node> &node);
    void backPropagation(const std::shared_ptr<Node> &node, int playerNb);
public:
    MonteCarlo();
    virtual ~MonteCarlo();
    const Point &findNextMove(const AI &ai, int playerNb);
};


#endif //GOMOKU_MONTECARLO_H
