//
// Created by Mathieu on 07/12/2017.
//

#include "State.h"

State::State() : ai(AI()), playerNb(0), visitCount(0), score(0) {}

State::State(std::unique_ptr<State> const &state) {
    ai = AI(state->ai);
    playerNb = state->getPlayer();
    score = state->getScore();
    visitCount = state->getVisitCount();
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

std::vector<State> &&State::getAllNextStates() {
    std::vector<State> states;
    std::vector<AI::Point> points = ai.getBestScoreSquares(NB_OF_BEST_SCORE_TO_SEARCH);

    for (auto &point: points) {
        State state;
        state.setPlayer(3 - playerNb)
        state.getAi().update_map((state.playerNb == 1 ? '0' : 'X'), point.x, point.y);
        states.push_back(state);
    }
    return std::move(states);
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
    std::vector<AI::Point> availablePositions = board.getEmptyPositions();
    int totalPossibilities = availablePositions.size();
    int selectRandom = (int) (Math.random() * ((totalPossibilities - 1) + 1));
    this.board.performMove(this.playerNo, availablePositions.get(selectRandom));
}
