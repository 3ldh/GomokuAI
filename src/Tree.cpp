//
// Created by Mathieu on 07/12/2017.
//

#include "Tree.h"

Tree::Tree() {
    root = std::make_shared<Node>();
}

Tree::~Tree() {

}

const std::shared_ptr<Node> &Tree::getRoot() const {
    return root;
}

void Tree::setRoot(std::shared_ptr<Node> &root) {
    Tree::root = std::move(root);
}

void Tree::addChild(std::shared_ptr<Node> parent, std::shared_ptr<Node> child) {
    parent->getChildren().push_back(child);
}


