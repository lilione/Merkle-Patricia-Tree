//
// Created by lilione on 2017/9/13.
//

#ifndef MERKLE_PARTRICIA_TREE_ACCOUNT_H
#define MERKLE_PARTRICIA_TREE_ACCOUNT_H


#include "ByteArray.h"
#include "uint256_t.h"

class Account {
public:
    unsigned int nonce;
    uint256_t balance;
    ByteArray rootHash;
    ByteArray codeHash;

    Account(unsigned int nonce, uint256_t balance, ByteArray rootHash, ByteArray codeHash):
            nonce(nonce), balance(balance), rootHash(rootHash), codeHash(codeHash) {}
};


#endif //MERKLE_PARTRICIA_TREE_ACCOUNT_H
