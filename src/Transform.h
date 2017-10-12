//
// Created by lilione on 2017/10/11.
//

#ifndef MERKLE_PARTRICIA_TREE_TRANSFORM_H
#define MERKLE_PARTRICIA_TREE_TRANSFORM_H


#include "Bytes.h"
#include "uint256_t.h"

class Transform {
public:

    static int fromHex(char _i);
    static char toHex(int _i);

    static Bytes stringToBytes(std::string st);

    static Bytes hexStringToBytes(std::string st);
    static ethash_h256_t hexStringToHash(std::string st);
    static uint256_t hexStringToUint256_t(std::string st);

    static std::string bytesToString(Bytes bytes);

    static uint256_t intStringToUint256_t(std::string st);


    static ethash_h256_t uint256_tToHash(uint256_t x);

    static Bytes intToBytes(int x);

    static std::string bytesToHexString(Bytes array);

};


#endif //MERKLE_PARTRICIA_TREE_TRANSFORM_H
