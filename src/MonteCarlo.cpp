//
// Created by Mathieu on 07/12/2017.
//

#include <Tree.h>
#include <UCT.h>
#include <limits>
#include <Timer.h>
#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {}

MonteCarlo::~MonteCarlo() {

}

const Point &MonteCarlo::findNextMove(const AI &ai, int playerNb) {

    Timer timer;
    Tree tree;
    const std::shared_ptr<Node> &root = tree.getRoot();

    opponent = 3 - playerNb;
    root->getState()->setAi(ai);
    root->getState()->setPlayer(opponent);
    timer.start();

    while (!timer.isTimeOverMilliseconds(4500)) {
        std::shared_ptr<Node> nextBestNode = findNextBestNode(root);
        expandNode(nextBestNode);
        std::shared_ptr<Node> nodeToExplore = nextBestNode;
        if (!nextBestNode->getChildren().empty()) {
            nodeToExplore = nextBestNode->getRandomChildNode();
        }
        int playResult = simulatePlay(nodeToExplore);
        backPropagation(nodeToExplore, playResult);
    }
    std::shared_ptr<Node> winnerNode = root->getChildWithMaxScore();
    return winnerNode->getState()->getAi().getPositionPlayed();
}

const std::shared_ptr<Node> MonteCarlo::findNextBestNode(const std::shared_ptr<Node> &rootNode) {
    std::shared_ptr<Node> node = rootNode;

    while (!node->getChildren().empty()) {
        node = UCT::findNodeWithBestUCT(node);
    }
    return node;
}

void MonteCarlo::expandNode(const std::shared_ptr<Node> &node) {
    std::vector<std::shared_ptr<State>> allNextStates = node->getState()->getAllNextStates();

    for (auto &state: allNextStates) {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(state);
        newNode->setParent(node);
        newNode->getState()->setPlayer(node->getState()->getAdversary());
        node->getChildren().push_back(newNode);
        if (node->getState()->getAi().checkStatus() == AI::WIN)
            break;
    }
}

int MonteCarlo::simulatePlay(const std::shared_ptr<Node> &node) {
    std::unique_ptr<Node> tmpNode = std::make_unique<Node>(node);
    std::unique_ptr<State> tmpState = std::make_unique<State>(tmpNode->getState());

    int gameStatus = tmpState->getAi().checkStatus();
    if (gameStatus == AI::LOOSE && tmpState->getAi().getPlayerNb() == 2 ||
        gameStatus == AI::WIN && tmpState->getAi().getPlayerNb() == 1) {
        tmpNode->getParent()->getState()->setScore(std::numeric_limits<int>::min());
        return gameStatus;
    }
    while (gameStatus == AI::IN_PROGRESS) {
        tmpState->togglePlayerNb();
        tmpState->randomPlay();
        gameStatus = tmpState->getAi().checkStatus();
    }
    return gameStatus;
}

void MonteCarlo::backPropagation(const std::shared_ptr<Node> &node, int playResult) {
    std::shared_ptr<Node> tmpNode = node;
    while (tmpNode != nullptr) {
        tmpNode->getState()->incrementVisit();
        if (tmpNode->getState()->getPlayer() == 2 && playResult == AI::WIN
            || tmpNode->getState()->getPlayer() == 1 && playResult == AI::LOOSE)
            tmpNode->getState()->addScore(WIN_SCORE);
        tmpNode = tmpNode->getParent();
    }
}
