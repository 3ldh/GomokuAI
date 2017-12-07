//
// Created by Mathieu on 07/12/2017.
//

#ifndef GOMOKU_STATE_H
#define GOMOKU_STATE_H


#include "AI.h"

class State {

#define NB_OF_BEST_SCORE_TO_SEARCH 20

private:
    AI ai;
    int playerNb;
    int visitCount;
    double score;

public:
    State();
    explicit State(std::unique_ptr<State> const &state);
    virtual ~State();


    void setAi(const AI &ai);
    const AI &getAi() const;
    AI &getAi();
    int getVisitCount() const;
    double getScore() const;

    void setScore(double score);

    void incrementVisit();
    int getPlayer() const;
    void setPlayer(int player);
    std::vector<State> &&getAllNextStates();
    int getAdversary();
    void togglePlayerNb();
    void randomPlay();
/*
    const std::vector<std::vector<char>> &getMap() const;
    const std::vector<std::vector<int>> &getScoreMap() const;
*/
};


#endif //GOMOKU_STATE_H
