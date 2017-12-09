//
// Created by Mathieu on 07/12/2017.
//

#include "UCT.h"
#include <limits>
#include <cmath>
#include <algorithm>

double UCT::uctValue(int totalVisitCount, double score, int nodeVisitCount) {
    if (nodeVisitCount == 0)
        return std::numeric_limits<int>::max();
    return (score / (double) nodeVisitCount) + 1.41f * sqrt(log(totalVisitCount) / (double) nodeVisitCount);
}


const std::shared_ptr<Node> UCT::findNodeWithBestUCT(std::shared_ptr<Node> const &node) {
    int parentVisitCount = node->getState()->getVisitCount();

    return *std::max_element(
            node->getChildren().begin(), node->getChildren().end(),
            [parentVisitCount](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
                return uctValue(parentVisitCount, a->getState()->getScore(), a->getState()->getVisitCount())
                       < uctValue(parentVisitCount, b->getState()->getScore(), b->getState()->getVisitCount()); });
}