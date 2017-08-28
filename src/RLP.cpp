//
// Created by lilione on 2017/8/23.
//

#include <sstream>
#include <iostream>
#include <vector>
#include "RLP.h"®

std::string RLP::encode(std::string st) {
    if (st.length() == 1 && (unsigned char)st[0] < 128) {
        return st;
    }
    else {
        return encodeLength(st.length(), 128) + st;
    }
}

std::string RLP::encode(TX tx) {
    /*std::string ret = encode(hexToBin(removeHexFormat(tx.from)))
                    + encode(hexToBin(removeHexFormat(tx.to)))
                    + encode(hexToBin(removeHexFormat(tx.value)));*/
    std::string ret = encode(hexToBin(removeHexFormat(tx.nonce)))
                      + encode(hexToBin(removeHexFormat(tx.gasPrice)))
                        + encode(hexToBin(removeHexFormat(tx.startGas)))
                          + encode(hexToBin(removeHexFormat(tx.to)))
                            + encode(hexToBin(removeHexFormat(tx.value)))
                              + encode(hexToBin(removeHexFormat(tx.data)))
                                + encode(hexToBin(removeHexFormat(tx.v)))
                                  + encode(hexToBin(removeHexFormat(tx.r)))
                                    + encode(hexToBin(removeHexFormat(tx.s)));
    return encodeLength(ret.length(), 192) + ret;
}

std::string RLP::encode(std::vector<std::string> list) {
    std::string ret = "";
    for (int i = 0; i < list.size(); i++) {
        ret += encode(hexToBin(removeHexFormat(list[i])));
    }
    return encodeLength(ret.length(), 192) + ret;
}

std::string RLP::encodeLength(int len, int offset) {
    //len should be less than 256**8
    std::string ret;
    if (len < 56) {
        ret = char(len + offset);
    }
    else {
        std::string BL = intToHex(len);
        ret = char(BL.length() + offset + 55) + BL;
    }
    return ret;
}

std::string RLP::removeHexFormat(std::string st) {
    if (st.length() > 1 && st[0] == '0' && st[1] == 'x') {
        return st.substr(2);
    }
    return st;
}

std::string RLP::intToHex(int x) {
    if (x == 0) {
        return "";
    }
    return intToHex(x / 256) + (char)(x % 256);
}

std::string RLP::hexToBin(std::string st) {
    //must of even length
    std::string ret = "";
    for (int i = 0; i + 1 < st.length(); i += 2) {
        ret += char(charToInt(st[i]) * 16 + charToInt(st[i + 1]));
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