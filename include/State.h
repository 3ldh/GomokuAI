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
    unsigned int index;

public:
    State();
    explicit State(std::shared_ptr<State> const &state);
    explicit State(AI const &ai);
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
    std::vector<std::shared_ptr<State>> getAllNextStates();
    int getAdversary();
    void togglePlayerNb();
    void randomPlay();
    void addScore(double s);
};


#endif //GOMOKU_STATE_H
