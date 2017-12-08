//
// Created by Mathieu on 07/12/2017.
//

#include <afxres.h>
#include <Tree.h>
#include <UCT.h>
#include <limits>
#include "MonteCarlo.h"

MonteCarlo::MonteCarlo() {}

MonteCarlo::~MonteCarlo() {

}

long MonteCarlo::getCurrentTime() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    return (time.wSecond * 1000) + time.wMilliseconds;
}

const AI::Point &MonteCarlo::findNextMove(const AI &ai, int playerNb) {

    long start = getCurrentTime();
    long end = start + 5 * 1000;
    Tree tree;
    const std::shared_ptr<Node> &root = tree.getRoot();
    root->getState()->setAi(ai);
    opponent = 3 - playerNb;

    while (getCurrentTime() < end) {
        std::cout << "Time : " << getCurrentTime() << std::endl;
        //Phase 1 selection
        std::shared_ptr<Node> nextBestNode = findNextBestNode(root);
        //Phase 2 expansion
        if (nextBestNode->getState()->getAi().checkStatus() == AI::IN_PROGRESS)
            expandNode(nextBestNode);
        //Phase 3  Simulation
        std::shared_ptr<Node> nodeToExplore = nextBestNode;
        if (nextBestNode->getChildren().size() > 0) {
            nodeToExplore = nextBestNode->getRandomChildNode();
        }
        int playResult = simulatePlay(nodeToExplore);

        // Phase 4 - Update
        backPropagation(nodeToExplore, playResult);
    }
}

const std::shared_ptr<Node> MonteCarlo::findNextBestNode(const std::shared_ptr<Node> rootNode) {
    std::shared_ptr<Node> node = rootNode;
    while (!node->getChildren().empty()) {
        std::cout << "Finding Next best node...." << std::endl;
        node = UCT::findNodeWithBestUCT(node);
    }
    return node;
}

void MonteCarlo::expandNode(std::shared_ptr<Node> node) {
    std::vector<std::shared_ptr<State>> allNextStates = node->getState()->getAllNextStates();

    std::cout << "SIZE NEXTSTATES " << allNextStates.size() << std::endl;
    for (auto &state: allNextStates) {
        std::cout << "Expanding Node...." << state.use_count() <<std::endl;
        std::shared_ptr<Node> newNode = std::make_shared<Node>(state);
        newNode->setParent(node);
        newNode->getState()->setPlayer(node->getState()->getAdversary());
        node->getChildren().push_back(newNode);
    }
}

int MonteCarlo::simulatePlay(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> tmpNode = std::make_shared<Node>(node);
    std::shared_ptr<State> tmpState = tmpNode->getState();

    int gameStatus = tmpState->getAi().checkStatus();
    if (gameStatus == opponent) {
        tmpNode->getParent()->getState()->setScore(std::numeric_limits<int>::min());
        return gameStatus;
    }
    while (gameStatus == AI::IN_PROGRESS) {
        std::cout << "Simulating random Play..." << std::endl;
        tmpState->togglePlayerNb();
        tmpState->randomPlay();
        gameStatus = tmpState->getAi().checkStatus();
    }
    return gameStatus;
}

void MonteCarlo::backPropagation(std::shared_ptr<Node> node, int playerNb) {
    std::shared_ptr<Node> tmpNode = node;
    while (tmpNode != nullptr) {
        std::cout << "Backpropagation..." << std::endl;
        tmpNode->getState()->incrementVisit();
        if (tmpNode->getState()->getPlayer() == playerNb)
            tmpNode->getState()->addScore(WIN_SCORE);
        tmpNode = tmpNode->getParent();
    }
}
