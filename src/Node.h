//
// Created by lilione on 2017/8/24.
//

#ifndef MERKLE_PARTRICIA_TREE_NODE_H
#define MERKLE_PARTRICIA_TREE_NODE_H


#include <cstdint>
#include <vector>
#include "ByteArray.h"

class Node {
public:
    std::vector<ByteArray> content;

    Node() {}

    Node(std::vector<ByteArray> content):
        content(content) {}

    void operator= (const Node& other) {
        this->content = other.content;
    }
};


#endif //MERKLE_PARTRICIA_TREE_NODE_H
