//
// Created by lilione on 2017/8/29.
//

#ifndef MERKLE_PARTRICIA_TREE_PROOF_H
#define MERKLE_PARTRICIA_TREE_PROOF_H


#include <string>
#include "Node.h"
#include "TX.h"

class Proof {
public:
    std::string path;
    TX tx;
    std::vector<Node> parentNodes;
    std::string rootHash;

    Proof(std::string path, TX tx, std::vector<Node> _parendNodes, std::string rootHash):
            path(path), tx(tx), rootHash(rootHash) {
        for (int i = 0; i < _parendNodes.size(); i++) {
            parentNodes.push_back(_parendNodes[i]);
        }
    }
};


#endif //MERKLE_PARTRICIA_TREE_PROOF_H
