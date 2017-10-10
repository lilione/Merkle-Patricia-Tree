//
// Created by lilione on 2017/8/31.
//

#include <string>
#include "ByteArray.h"

ByteArray ByteArray::substr(int start, int end) {
    ByteArray ret;
    for (int i = start; i < end; i++) {
        ret.data.push_back(data[i]);
    }
    return ret;
}

std::string ByteArray::toString() {
    std::string st;
    for (int i = 0; i < data.size(); i++) {
        st += char(data[i]);
    }
    return st;
}