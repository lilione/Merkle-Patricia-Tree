//
// Created by lilione on 2017/8/31.
//

#include <string>
#include "ByteArray.h"

ByteArray::ByteArray(uint8_t value) {
    data.push_back(value);
}

ByteArray ByteArray::operator+ (const ByteArray& other) {
    ByteArray ret;
    for (int i = 0; i < this->data.size(); i++) {
        ret.data.push_back(this->data[i]);
    }
    for (int i = 0; i < other.data.size(); i++) {
        ret.data.push_back(other.data[i]);
    }
    return ret;
}

bool ByteArray::operator== (const ByteArray& other) {
    if (this->data.size() != other.data.size()) return 0;
    for (int i = 0; i < this->data.size(); i++) {
        if (this->data[i] != other.data[i]) return 0;
    }
    return 1;
}

bool ByteArray::operator!= (const ByteArray& other) {
    if (this->data.size() != other.data.size()) return 1;
    for (int i = 0; i < this->data.size(); i++) {
        if (this->data[i] != other.data[i]) return 1;
    }
    return 0;
}

void ByteArray::operator= (const ByteArray& other) {
    this->data = other.data;
}

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