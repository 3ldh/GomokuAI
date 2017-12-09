//
// Created by Mathieu on 07/12/2017.
//

#ifndef GOMOKU_UCT_H
#define GOMOKU_UCT_H


#include "Node.h"

class UCT {

public:
    static double uctValue(int totalVisitCount, double score, int nodeVisitCount);
    static const std::shared_ptr<Node> findNodeWithBestUCT(std::shared_ptr<Node> const &node);
};


#endif //GOMOKU_UCT_H
