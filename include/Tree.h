//
// Created by Mathieu on 07/12/2017.
//

#ifndef GOMOKU_TREE_H
#define GOMOKU_TREE_H


#include "Node.h"

class Tree {
    std::shared_ptr<Node> root;

public:
    Tree();
    virtual ~Tree();

    const std::shared_ptr<Node> &getRoot() const;
    void setRoot(std::shared_ptr<Node> &root);
    void addChild(std::shared_ptr<Node> parent, std::shared_ptr<Node> child); }
;


#endif //GOMOKU_TREE_H
