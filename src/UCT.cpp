//
// Created by Mathieu on 07/12/2017.
//

#include "UCT.h"
#include <limits>
#include <cmath>

double UCT::uctValue(int totalVisitCount, double score, int nodeVisitCount) {
    if (nodeVisitCount == 0)
        return std::numeric_limits<int>::max();
    return (score / (double) nodeVisitCount) + 1.41f * sqrt(log(totalVisitCount) / (double) nodeVisitCount);
}


const std::shared_ptr<Node> UCT::findNodeWithBestUCT(std::shared_ptr<Node> const &node) {
    int parentVisitCount = node->getState()->getVisitCount();
    double maxScore = 0;
    std::shared_ptr<Node> bestNode;

    for (const auto &n : node->getChildren()) {
        double score = uctValue(parentVisitCount, n->getState()->getScore(),
                                n->getState()->getVisitCount());
        if (maxScore < score) {
            maxScore = score;
            bestNode = n;
        }
    }
    return bestNode;
}