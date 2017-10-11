//
// Created by lilione on 2017/10/11.
//

#ifndef MERKLE_PARTRICIA_TREE_TRANSFORM_H
#define MERKLE_PARTRICIA_TREE_TRANSFORM_H


#include "Bytes.h"

class Transform {

    Bytes stringToBytes(std::string st);

public:
    static std::string bytesToString(Bytes bytes);
};


#endif //MERKLE_PARTRICIA_TREE_TRANSFORM_H
