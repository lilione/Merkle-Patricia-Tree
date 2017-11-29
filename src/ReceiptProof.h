//
// Created by lilione on 2017/11/22.
//

#ifndef MERKLE_PARTRICIA_TREE_RECEIPTPROOF_H
#define MERKLE_PARTRICIA_TREE_RECEIPTPROOF_H

#include "Proof.h"

class ReceiptProof : public Proof {
public:
    Bytes blockNumber;
    ReceiptProof(Bytes key, std::vector<Node> path, Bytes blockNumber):
            Proof(key, path), blockNumber(blockNumber) {}
};


#endif //MERKLE_PARTRICIA_TREE_RECEIPTPROOF_H
