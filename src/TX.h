//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_TX_H
#define MERKLE_PARTRICIA_TREE_TX_H


#include <string>

class TX {
public:
    /*std::string from;
    std::string to;
    std::string value;*/
    std::string nonce, gasPrice, startGas, to, value, data, v, r, s;
};


#endif //MERKLE_PARTRICIA_TREE_TX_H
