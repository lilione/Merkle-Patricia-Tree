//
// Created by lilione on 2017/8/31.
//

#ifndef MERKLE_PARTRICIA_TREE_BYTEARRAY_H
#define MERKLE_PARTRICIA_TREE_BYTEARRAY_H


#include <cstdint>
#include <vector>
#include <cstring>

class ByteArray {
public:
    std::vector<uint8_t> data;

    ByteArray() {}

    ByteArray(uint8_t);

    ByteArray operator+ (const ByteArray&);

    bool operator== (const ByteArray&);

    bool operator!= (const ByteArray&);

    void operator= (const ByteArray&);

    ByteArray substr(int, int);

    std::string toString();

    static ByteArray stringToByteArray(std::string);

    static void output(ByteArray);
    static void outputHex(ByteArray);
};


#endif //MERKLE_PARTRICIA_TREE_BYTEARRAY_H
