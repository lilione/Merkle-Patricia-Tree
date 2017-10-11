//
// Created by lilione on 2017/10/11.
//

#include <string>

#include "Transform.h"
#include "Bytes.h"

Bytes Transform::stringToBytes(std::string st) {
    Bytes ret;
    for (int i = 0; i < st.length(); i++) {
        ret.data.push_back(uint8_t(st[i]));
    }
    return ret;
}

std::string Transform::bytesToString(Bytes bytes) {
    std::string st;
    for (int i = 0; i < bytes.data.size(); i++) {
        st += char(bytes.data[i]);
    }
    return st;
}
