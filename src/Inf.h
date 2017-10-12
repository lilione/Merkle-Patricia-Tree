//
// Created by lilione on 2017/10/12.
//

#ifndef MERKLE_PARTRICIA_TREE_INF_H
#define MERKLE_PARTRICIA_TREE_INF_H

#include "Bytes.h"
#include "uint256_t.h"

class Inf {
    Bytes pos, tokenAddr, userAddr;
    uint256_t value;

    Inf() {}

    Inf(Bytes pos, Bytes tokenAddr, Bytes userAddr, uint256_t value):
            pos(pos), tokenAddr(tokenAddr), userAddr(userAddr), value(value) {}

public:
    static Inf getInf();
};


#endif //MERKLE_PARTRICIA_TREE_INF_H
