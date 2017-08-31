//
// Created by lilione on 2017/8/23.
//

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include "RLP.h"

const int offset_string = 128;
const int offset_list = 192;

ByteArray RLP::encode(ByteArray input) {
    if (input.data.size() == 1 && input.data[0] < 128) {
        return input;
    }
    return encodeLength(input.data.size(), 128) + input;
}

ByteArray RLP::encode(std::vector<ByteArray> list) {
    ByteArray output;
    for (int i = 0; i < list.size(); i++) {
        output = output + encode(list[i]);
    }
    return encodeLength(output.data.size(), 192) + output;
}

ByteArray RLP::encodeLength(int L, int offset) {
    //len should be less than 256**8
    if (L < 56) {
        return ByteArray(L + offset);
    }
    ByteArray BL = toBinary(L);
    return ByteArray(BL.data.size() + offset + 55) + BL;
}

ByteArray RLP::toBinary(int x) {
    ByteArray ret;
    if (x != 0) {
        ret = toBinary(x / 256) + ByteArray(x % 256);
    }
    return ret;
}

ByteArray RLP::hexToBin(std::string st) {
    //must of even length
    ByteArray ret;
    for (int i = 0; i < st.length(); i += 2) {
        ret = ret + ByteArray(charToInt(st[i]) * 16 + charToInt(st[i + 1]));
    }
    return ret;
}

int RLP::charToInt(char ch) {
    if (isdigit(ch)) {
        return ch - '0';
    }
    if (isupper(ch)) {
        return ch - 'A' + 10;
    }
    if (islower(ch)) {
        return ch - 'a' + 10;
    }
}

std::string RLP::binToHex(ByteArray array) {
    std::string ret;
    for (int i = 0; i < array.data.size(); i++) {
        int now = array.data[i];
        ret += intToChar(now / 16);
        ret += intToChar(now % 16);
    }
    return ret;
}

char RLP::intToChar(int x) {
    if (x < 10) {
        return '0' + x;
    }
    return 'a' + x - 10;
}

std::string RLP::toString(ByteArray array) {
    std::string ret = "";
    for (int i = 0; i < array.data.size(); i++) {
        ret += char(array.data[i]);
    }
    return ret;
}

Proof RLP::decode(ByteArray input) {
    std::vector<ByteArray> elements = decode_list(input);
    ByteArray path = decode_string(elements[0]);
    std::vector<ByteArray> tx = decode_list(elements[1]);
    std::vector<ByteArray> parentNodes_list = decode_list(elements[2]);
    std::vector<Node> parentNodes;
    for (int i = 0; i < parentNodes_list.size(); i++) {
        parentNodes.push_back(Node(decode_list(parentNodes_list[i])));
    }
    ByteArray rootHash = decode_string(elements[3]);
    return Proof(path, tx, parentNodes, rootHash);
}

std::vector<ByteArray> RLP::decode_list(ByteArray input) {
    int pos = 0, len = decodeLength(input, pos);
    int end = len + pos;
    std::vector<ByteArray> ret;
    while (pos < end) {
        int now = decodeLength(input, pos);
        ret.push_back(input.substr(pos, pos + now));
        pos += now;
    }
    return ret;
}

ByteArray RLP::decode_string(ByteArray input) {
    int pos = 0, len = decodeLength(input, pos);
    return input.substr(pos, pos + len);
}

int RLP::decodeLength(ByteArray input, int& pos) {
    int len, offset;
    if (input.data[pos] < offset_list) {
        if (input.data[pos] < 55) {
            return 1;
        }
        offset = offset_string;
    }
    else {
        offset = offset_list;
    }
    if (input.data[pos] <= offset + 55) {
        len = input.data[pos++] - offset;
    }
    else {
        int now = input.data[pos++] - offset - 55;
        len = 0;
        for (int i = 0; i < now; i++) {
            len = len * 256 + input.data[pos++];
        }
    }
    return len;
}