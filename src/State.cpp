//
// Created by Mathieu on 07/12/2017.
//

#include <limits>
#include "State.h"

State::State() : ai(AI()), playerNb(0), visitCount(0), score(0) {}

State::State(std::shared_ptr<State> const &state) {
    ai = AI(state->ai);
    playerNb = state->getPlayer();
    score = state->getScore();
    visitCount = state->getVisitCount();
    ai.setPlayerNb(playerNb);
}

State::State(AI const &ai) {
    this->ai = AI(ai);
    playerNb = 0;
    visitCount = 0;
    score = 0;
}

State::~State() {

}

const AI &State::getAi() const {
    return ai;
}

int State::getVisitCount() const {
    return visitCount;
}

double State::getScore() const {
    return score;
}

void State::incrementVisit() {
    ++visitCount;
}

void State::setAi(const AI &ai) {
    State::ai = ai;
}

int State::getPlayer() const {
    return playerNb;
}

void State::setPlayer(int player) {
    State::playerNb = player;
}

std::vector<std::shared_ptr<State>> State::getAllNextStates() {
    std::vector<std::shared_ptr<State>> states;
    std::vector<Point> points = ai.getBestScoreSquares(NB_OF_BEST_SCORE_TO_SEARCH);

    for (auto &point: points) {
        std::shared_ptr<State> newState = std::make_shared<State>(ai);
//        std::cout << point << std::endl;
        newState->setPlayer(3 - playerNb);
        newState->getAi().setPlayerNb(newState->getPlayer());
        newState->getAi().update_map((newState->getPlayer() == 2 ? '0' : 'X'), point.x, point.y);
        newState->getAi().update_score_map(point.x, point.y);
//        newState->getAi().print_score_map();
        states.push_back(newState);
    }
    return states;
}

AI &State::getAi() {
    return ai;
}

int State::getAdversary() {
    return 3 - playerNb;
}

void State::setScore(double score) {
    State::score = score;
}

void State::togglePlayerNb() {
    playerNb = 3 - playerNb;
}

void State::randomPlay() {
    std::vector<Point> points = ai.getBestScoreSquares(NB_OF_BEST_SCORE_TO_SEARCH);

    int r = AI::randomRange(0, points.size());
//    std::cout << "RandomPlay for ai nb " << playerNb << " " << points[r] << std::endl;

    ai.update_map(playerNb == 2 ? 'O' : 'X', points[r].x, points[r].y);
    ai.update_score_map(points[r].x, points[r].y);
  //  ai.printMap();
}

void State::addScore(double s) {
    if (s != std::numeric_limits<int>::min())
        score += s;
}

