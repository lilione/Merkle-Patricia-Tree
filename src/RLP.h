//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_RLP_H
#define MERKLE_PARTRICIA_TREE_RLP_H


#include <cstdint>
#include <vector>
#include "ByteArray.h"
#include "Proof.h"
#include "Account.h"


class RLP {
public:
    ByteArray encodeString(ByteArray);
    ByteArray encodeList(std::vector<ByteArray>);
    ByteArray encodeLength(int, int);
    ByteArray intToByteArray(int);
    ByteArray hexStringToByteArray(std::string);
    int charToInt(char);
    std::string byteArrayToHexString(ByteArray);
    char intToChar(int);
    std::pair<Proof, Proof> decodeProof(ByteArray);
    Account decodeAccount(ByteArray);
    std::vector<ByteArray> decodeList(ByteArray);
    ByteArray remove_length(ByteArray);
    int decodeLength(ByteArray, int&);
};

#endif //MERKLE_PARTRICIA_TREE_RLP_H
