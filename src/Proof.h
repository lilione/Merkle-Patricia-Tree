//
// Created by lilione on 2017/8/29.
//

#ifndef MERKLE_PARTRICIA_TREE_PROOF_H
#define MERKLE_PARTRICIA_TREE_PROOF_H


#include "Bytes.h"
#include "Node.h"

class Proof {
public:
    Bytes key;
    std::vector<Node> path;
    Bytes pos, tokenAddr, userAddr;

    Proof() {}

    Proof(Bytes key, std::vector<Node> path):
            key(key), path(path) {}

    Proof(Bytes key, std::vector<Node> path, Bytes pos, Bytes tokenAddr, Bytes userAddr):
            key(key), path(path), pos(pos), tokenAddr(tokenAddr), userAddr(userAddr) {}

    static void output(Proof);
};


#endif //MERKLE_PARTRICIA_TREE_PROOF_H
