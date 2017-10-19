//
// Created by lilione on 2017/10/12.
//

#ifndef MERKLE_PARTRICIA_TREE_INF_H
#define MERKLE_PARTRICIA_TREE_INF_H

#include "Bytes.h"
#include "uint256_t.h"
#include "Queue.h"

class Inf {
public:
    uint pos;
    Address tokenAddr, userAddr;
    uint256_t value;

    Inf() {}

    Inf(uint pos, Address tokenAddr, Address userAddr, uint256_t value):
            pos(pos), tokenAddr(tokenAddr), userAddr(userAddr), value(value) {}

    static Inf getInf(const Queue&);
};


#endif //MERKLE_PARTRICIA_TREE_INF_H
