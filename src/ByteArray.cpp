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

ByteArray ByteArray::stringToByteArray(std::string st) {
    ByteArray ret;
    for (int i = 0; i < st.length(); i++) {
        ret.data.push_back(uint8_t(st[i]));
    }
    return ret;
}

void ByteArray::output(ByteArray byteArray) {
    for (int i = 0; i < byteArray.data.size(); i++) {
        printf("%d ", byteArray.data[i]);
    }
    printf("\n");
}

void ByteArray::outputHex(ByteArray byteArray) {
    for (int i = 0; i < byteArray.data.size(); i++) {
        printf("%02x", byteArray.data[i]);
    }
    printf("\n");
}