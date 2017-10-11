//
// Created by lilione on 2017/8/24.
//

#ifndef MERKLE_PARTRICIA_TREE_NODE_H
#define MERKLE_PARTRICIA_TREE_NODE_H


#include <cstdint>
#include <vector>
#include "Bytes.h"

class Node {
public:
    std::vector<Bytes> content;

    Node() {}

    Node(std::vector<Bytes> content):
        content(content) {}

    void operator= (const Node& other) {
        this->content = other.content;
    }
};


#endif //MERKLE_PARTRICIA_TREE_NODE_H
