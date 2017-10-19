//
// Created by lilione on 2017/8/29.
//

#ifndef MERKLE_PARTRICIA_TREE_PROOF_H
#define MERKLE_PARTRICIA_TREE_PROOF_H

#include "Bytes.h"
#include "Node.h"
#include "Address.h"

class Proof {
public:
    Bytes key;
    std::vector<Node> path;
    uint pos;
    Address tokenAddr, userAddr;

    Proof() {}

    Proof(Bytes key, std::vector<Node> path):
            key(key), path(path) {}

    Proof(Bytes key, std::vector<Node> path, uint pos, Address tokenAddr, Address userAddr):
            key(key), path(path), pos(pos), tokenAddr(tokenAddr), userAddr(userAddr) {}

    static void output(Proof);

    static std::pair<Bytes, bool> verifyProof(std::string, std::vector<Node>, ethash_h256_t);

    static int removeFlag(std::string, std::string, int);
};


#endif //MERKLE_PARTRICIA_TREE_PROOF_H
