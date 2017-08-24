//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_RLP_H
#define MERKLE_PARTRICIA_TREE_RLP_H


#include <string>
#include "TX.h"

class RLP {
public:
    std::string encode(std::string);
    std::string encode(TX);
    std::string encode(std::vector<std::string>);

    std::string encodeLength(int, int);

    std::string removeHexFormat(std::string);

    std::string intToHex(int);
    std::string hexToBin(std::string);
    int charToInt(char);
};


#endif //MERKLE_PARTRICIA_TREE_RLP_H
