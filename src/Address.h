//
// Created by lilione on 2017/10/12.
//

#ifndef MERKLE_PARTRICIA_TREE_ADDRESS_H
#define MERKLE_PARTRICIA_TREE_ADDRESS_H

#include <cstdint>

using byte = uint8_t;

class Address {
public:
    byte data[20];

    static void outputHex(Address);
};


#endif //MERKLE_PARTRICIA_TREE_ADDRESS_H
