//
// Created by lilione on 2017/8/29.
//

#ifndef MERKLE_PARTRICIA_TREE_PROOF_H
#define MERKLE_PARTRICIA_TREE_PROOF_H


#include "ByteArray.h"
#include "Node.h"

class Proof {
public:
    ByteArray key;
    std::vector<Node> path;

    Proof() {}

    Proof(ByteArray key, std::vector<Node> path):
            key(key), path(path) {}

    static void output(Proof);
};


#endif //MERKLE_PARTRICIA_TREE_PROOF_H
