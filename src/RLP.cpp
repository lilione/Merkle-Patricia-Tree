//
// Created by lilione on 2017/8/23.
//

#include <sstream>
#include <iostream>
#include <vector>
#include "RLP.h"
#include "Node.h"
#include "Proof.h"

std::string RLP::encode(std::string st) {
    st = hexToBin(removeHexFormat(st));
    if (st.length() == 1 && (unsigned char)st[0] < 128) {
        return st;
    }
    else {
        return encodeLength(st.length(), 128) + st;
    }
}

std::string RLP::encode(TX tx) {
    std::string ret = encode(tx.nonce)
                      + encode(tx.gasPrice)
                        + encode(tx.startGas)
                          + encode(tx.to)
                            + encode(tx.value)
                              + encode(tx.data)
                                + encode(tx.v)
                                  + encode(tx.r)
                                    + encode(tx.s);
    return encodeLength(ret.length(), 192) + ret;
}

std::string RLP::encode(std::vector<std::string> list) {
    std::string ret = "";
    for (int i = 0; i < list.size(); i++) {
        ret += encode(list[i]);
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
        ret += byteToChar(st.substr(i, 2));
    }
    return ret;
}

char RLP::byteToChar(std::string st) {
    return char(charToInt(st[0]) * 16 + charToInt(st[1]));
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

char RLP::intToChar(int x) {
    if (x < 10) {
        return '0' + x;
    }
    return 'a' + x - 10;
}

std::string RLP::binToHex(std::string st) {
    std::string ret = "";
    for (int i = 0; i < st.length(); i++) {
        int now = (st[i] + 256) % 256;
        ret += intToChar(now / 16);
        ret += intToChar(now % 16);
    }
    return ret;
}

int RLP::decode_list(int& pos, std::string st) {
    int ret;
    if ((st[pos] + 256) % 256 <= 247) {
        ret = (st[pos++] - 192 + 256) % 256;
    }
    else {
        int now = (st[pos++] - 192 - 55 + 256) % 256;
        ret = 0;
        while (now > 0) {
            ret = ret * 256 + (st[pos++] + 256) % 256;
            now--;
        }
    }
    return ret;
}

std::string RLP::decode_string(int& pos, std::string st, int& len) {
    std::string ret;
    if ((st[pos] + 256) % 256 <= 127) {
        len = 1;
        ret = st[pos++];
    }
    else {
        if ((st[pos] + 256) % 256 <= 183) {
            len = (st[pos++] - 128 + 256) % 256;
        }
        else {
            int now = (st[pos++] - 128 - 55 + 256) % 256;
            len = 0;
            while (now > 0) {
                len = len * 256 + ((int)st[pos++] + 256) % 256;
                now--;
            }
        }
        ret = st.substr(pos, len);
        pos += len;
    }
    return ret;
}

Proof RLP::decode(std::string st) {
    int pos = 0;

    int len = decode_list(pos, st);

    //path
    std::string path_st = decode_string(pos, st, len);
    int path_pos = 0;
    std::string path = binToHex(decode_string(path_pos, path_st, len));

    //tx
    std::string tx_st = decode_string(pos, st, len);
    TX tx;
    int tx_pos = 0;
    len = decode_list(tx_pos, tx_st);
    tx.nonce = binToHex(decode_string(tx_pos, tx_st, len));
    tx.gasPrice = binToHex(decode_string(tx_pos, tx_st, len));
    tx.startGas = binToHex(decode_string(tx_pos, tx_st, len));
    tx.to = binToHex(decode_string(tx_pos, tx_st, len));
    tx.value = binToHex(decode_string(tx_pos, tx_st, len));
    tx.data = binToHex(decode_string(tx_pos, tx_st, len));
    tx.v = binToHex(decode_string(tx_pos, tx_st, len));
    tx.r = binToHex(decode_string(tx_pos, tx_st, len));
    tx.s = binToHex(decode_string(tx_pos, tx_st, len));

    //parentNodes
    std::vector<Node> parentNodes;
    std::string parentNodes_dim0_st = decode_string(pos, st, len);
    int parentNodes_dim0_pos = 0;
    len = decode_list(parentNodes_dim0_pos, parentNodes_dim0_st);
    while (parentNodes_dim0_pos < parentNodes_dim0_st.length()) {
        Node node;
        std::string parentNodes_dim1_st = decode_string(parentNodes_dim0_pos, parentNodes_dim0_st, len);
        int parentNodes_dim1_pos = 0;
        len = decode_list(parentNodes_dim1_pos, parentNodes_dim1_st);
        while (parentNodes_dim1_pos < parentNodes_dim1_st.length()) {
            std::string tmp = decode_string(parentNodes_dim1_pos, parentNodes_dim1_st, len);
            node.content.push_back(binToHex(tmp));
        }
        parentNodes.push_back(node);
    }

    //rootHash
    std::string rootHash_st = decode_string(pos, st, len);
    int rootHash_pos = 0;
    std::string rootHash = binToHex(decode_string(rootHash_pos, rootHash_st, len));

    return Proof(path, tx, parentNodes, rootHash);
}