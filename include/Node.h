//
// Created by Mathieu on 07/12/2017.
//

#ifndef GOMOKU_NODE_H
#define GOMOKU_NODE_H


#include <vector>
#include <Memory>
#include "State.h"

class Node {

    std::shared_ptr<State> state;
    std::shared_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;

public:
    Node();
    explicit Node(const std::shared_ptr<Node> &node);
    explicit Node(const std::shared_ptr<State> &state);

    Node &operator=(Node const &node);
    virtual ~Node();
    void setState(std::shared_ptr<State> const &state);
    const std::shared_ptr<State> &getState() const;
    const std::shared_ptr<Node> &getParent() const;
    void setParent(std::shared_ptr<Node> const &parent);
    std::vector<std::shared_ptr<Node>> &getChildren();
    const std::vector<std::shared_ptr<Node>> &getChildren() const;
    void setChildren(const std::vector<std::shared_ptr<Node>> &children);
    std::shared_ptr<Node> getRandomChildNode();
    const std::shared_ptr<Node> getChildWithMaxScore() const;
};


#endif //GOMOKU_NODE_H
