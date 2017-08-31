//
// Created by lilione on 2017/8/29.
//

#ifndef MERKLE_PARTRICIA_TREE_PROOF_H
#define MERKLE_PARTRICIA_TREE_PROOF_H


#include "ByteArray.h"
#include "Node.h"

class Proof {
public:
    ByteArray path;
    std::vector<ByteArray> tx;
    std::vector<Node> parentNodes;
    ByteArray rootHash;

    Proof(ByteArray path, std::vector<ByteArray> tx, std::vector<Node> parentNodes, ByteArray rootHash):
            path(path), tx(tx), parentNodes(parentNodes), rootHash(rootHash) {}
};


#endif //MERKLE_PARTRICIA_TREE_PROOF_H
