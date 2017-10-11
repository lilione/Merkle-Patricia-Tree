//
// Created by lilione on 2017/8/31.
//

#ifndef MERKLE_PARTRICIA_TREE_BYTEARRAY_H
#define MERKLE_PARTRICIA_TREE_BYTEARRAY_H


#include <cstdint>
#include <vector>
#include <cstring>
#include "../libethash/ethash.h"

class Bytes {
public:
    std::vector<uint8_t> data;

    Bytes() {}

    Bytes(uint8_t);

    Bytes operator+ (const Bytes&);

    bool operator== (const Bytes&);

    bool operator!= (const Bytes&);

    void operator= (const Bytes&);

    Bytes substr(int, int);

    std::string toString();

    static Bytes stringToByteArray(std::string);

    static void output(Bytes);
    static void outputHex(Bytes);

    ethash_h256 hashToBytes(const Bytes &);
};


#endif //MERKLE_PARTRICIA_TREE_BYTEARRAY_H
