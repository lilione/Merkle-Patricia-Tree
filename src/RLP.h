//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_RLP_H
#define MERKLE_PARTRICIA_TREE_RLP_H


#include <cstdint>
#include <vector>
#include "ByteArray.h"
#include "Proof.h"

class RLP {
public:
    ByteArray encode(ByteArray);
    ByteArray encode(std::vector<ByteArray>);
    ByteArray encodeLength(int, int);
    ByteArray toBinary(int);
    ByteArray hexToBin(std::string);
    int charToInt(char);
    std::string binToHex(ByteArray);
    char intToChar(int);
    std::string toString(ByteArray);
    Proof decode(ByteArray);
    std::vector<ByteArray> decode_list(ByteArray);
    ByteArray decode_string(ByteArray);
    int decodeLength(ByteArray, int&);
};

#endif //MERKLE_PARTRICIA_TREE_RLP_H
