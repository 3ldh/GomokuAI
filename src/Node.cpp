//
// Created by Mathieu on 07/12/2017.
//

#include "Node.h"

#include <utility>

Node::~Node() {}

Node::Node() {
    state = std::make_shared<State>();
    parent = nullptr;
}

Node::Node(const std::shared_ptr<State> &state) {
    Node::state = std::make_shared<State>(state);
    std::cout << "YOLOOO..." << state.use_count() << std::endl;
    parent = nullptr;
}

Node::Node(const std::shared_ptr<Node> &node) {
    state = node->getState();
    if (node->getParent() != nullptr)
        parent = node->getParent();
    for (int i = 0; i < node->getChildren().size(); ++i) {
        children.push_back(std::make_shared<Node>());
    }
}

Node &Node::operator=(Node const &node) {
    state = node.getState();
    parent = node.getParent();
    children = node.getChildren();
}

void Node::setState(std::shared_ptr<State> const &state) {
    Node::state = state;
}

std::shared_ptr<State> Node::getState() const {
    return state;
}

std::shared_ptr<Node> Node::getParent() const {
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






