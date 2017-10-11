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

    ByteArray(uint8_t value) {
        data.push_back(value);
    }

    ByteArray operator+ (const ByteArray& other) {
        ByteArray ret;
        for (int i = 0; i < this->data.size(); i++) {
            ret.data.push_back(this->data[i]);
        }
        for (int i = 0; i < other.data.size(); i++) {
            ret.data.push_back(other.data[i]);
        }
        return ret;
    }

    bool operator== (const ByteArray& other) {
        if (this->data.size() != other.data.size()) return 0;
        for (int i = 0; i < this->data.size(); i++) {
            if (this->data[i] != other.data[i]) return 0;
        }
        return 1;
    }

    void operator= (const ByteArray& other) {
        this->data = other.data;
    }

    ByteArray substr(int, int);

    std::string toString();

    static ByteArray stringToByteArray(std::string);

    static void output(ByteArray);
    static void outputHex(ByteArray);
};


#endif //MERKLE_PARTRICIA_TREE_BYTEARRAY_H
