//
// Created by Mathieu on 07/12/2017.
//

#include "Node.h"

#include <algorithm>

Node::~Node() {}

Node::Node() {
    state = std::make_shared<State>();
    parent = nullptr;
}

Node::Node(const std::shared_ptr<State> &state) {
    Node::state = state;
    parent = nullptr;
}

Node::Node(const std::shared_ptr<Node> &node) {
    state = node->getState();
    if (node->getParent() != nullptr)
        parent = node->getParent();
    for (unsigned int i = 0; i < node->getChildren().size(); ++i) {
        children.push_back(std::make_shared<Node>());
    }
}

Node &Node::operator=(Node const &node) {
    if (this != &node) {
        state = node.getState();
        parent = node.getParent();
        children = node.getChildren();
    }
    return *this;
}

void Node::setState(std::shared_ptr<State> const &state) {
    Node::state = state;
}

const std::shared_ptr<State> &Node::getState() const {
    return state;
}

const std::shared_ptr<Node> &Node::getParent() const {
    return parent;
}

void Node::setParent(std::shared_ptr<Node> const &parent) {
    Node::parent = parent;
}

std::vector<std::shared_ptr<Node>> &Node::getChildren() {
    return children;
}

const std::vector<std::shared_ptr<Node>> &Node::getChildren() const {
    return children;
}

void Node::setChildren(const std::vector<std::shared_ptr<Node>> &children) {
    Node::children = children;
}

std::shared_ptr<Node> Node::getRandomChildNode() {
    int r = AI::randomRange(0, children.size());
    return children[r];
}

const std::shared_ptr<Node> Node::getChildWithMaxScore() const {
    return *std::max_element(children.begin(), children.end(),
                     [](std::shared_ptr<Node> a, std::shared_ptr<Node> b){
                         return a->getState()->getScore() < b->getState()->getScore(); });
}






