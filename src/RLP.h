//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_RLP_H
#define MERKLE_PARTRICIA_TREE_RLP_H

#include <cstdint>
#include <vector>

#include "Bytes.h"
#include "Proof.h"
#include "Account.h"

class RLP {
public:
    Bytes encodeString(Bytes);
    Bytes encodeList(std::vector<Bytes>);
    Bytes encodeLength(int, int);
    Bytes intToByteArray(int);
    Bytes hexStringToByteArray(std::string);
    int charToInt(char);
    std::string byteArrayToHexString(Bytes);
    char intToChar(int);
    std::pair<Proof, Proof> decodeProof(Bytes);
    Account decodeAccount(Bytes);
    std::vector<Bytes> decodeList(Bytes);
    Bytes remove_length(Bytes);
    int decodeLength(Bytes, int&);
};

#endif //MERKLE_PARTRICIA_TREE_RLP_H
