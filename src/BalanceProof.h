//
// Created by lilione on 2017/10/24.
//

#ifndef MERKLE_PARTRICIA_TREE_BALANCEPROOF_H
#define MERKLE_PARTRICIA_TREE_BALANCEPROOF_H

#include "Proof.h"

class BalanceProof : public Proof {
public:
    unsigned int pos;
    Address tokenAddr, userAddr;

    BalanceProof(Bytes key, std::vector<Node> path, unsigned int pos, Address tokenAddr, Address userAddr):
        Proof(key, path), pos(pos), tokenAddr(tokenAddr), userAddr(userAddr) {}
};


#endif //MERKLE_PARTRICIA_TREE_BALANCEPROOF_H
