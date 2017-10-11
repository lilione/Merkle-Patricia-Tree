//
// Created by lilione on 2017/8/23.
//

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include "RLP.h"
#include "Keccak.h"

const int offset_string = 128;
const int offset_list = 192;

ByteArray RLP::encodeString(ByteArray input) {
    if (input.data.size() == 1 && input.data[0] < 128) {
        return input;
    }
    return encodeLength(input.data.size(), 128) + input;
}

ByteArray RLP::encodeList(std::vector<ByteArray> list) {
    ByteArray ret;
    for (int i = 0; i < list.size(); i++) {
        ret = ret + list[i];
    }
    return encodeLength(ret.data.size(), 192) + ret;
}

ByteArray RLP::encodeLength(int L, int offset) {
    //len should be less than 256**8
    if (L < 56) {
        return ByteArray(L + offset);
    }
    ByteArray BL = intToByteArray(L);
    return ByteArray(BL.data.size() + offset + 55) + BL;
}

ByteArray RLP::intToByteArray(int x) {
    ByteArray ret;
    if (x != 0) {
        ret = intToByteArray(x / 256) + ByteArray(x % 256);
    }
    return ret;
}

ByteArray RLP::hexStringToByteArray(std::string st) {
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

std::string RLP::byteArrayToHexString(ByteArray array) {
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

std::pair<Proof, Proof> RLP::decodeProof(ByteArray input) {
    Keccak keccak;
    RLP rlp;

    std::vector<ByteArray> elements = decodeList(input);
    std::vector<ByteArray> path_list = decodeList(elements[0]);
    std::vector<Node> path;
    for (int i = 0; i < path_list.size(); i++) {
        path.push_back(Node(decodeList(path_list[i])));
    }
    ByteArray key = RLP::hexStringToByteArray(keccak(remove_length(elements[1]).toString()));
    Proof accoutProof = Proof(key, path);

    path_list = decodeList(elements[2]);
    path.clear();
    for (int i = 0; i < path_list.size(); i++) {
        path.push_back(Node(decodeList(path_list[i])));
    }

    ByteArray userAddr = remove_length(elements[3]);
    ByteArray tokenAddr = remove_length(elements[4]);
    ByteArray pos = remove_length(elements[5]);

    key = RLP::hexStringToByteArray(keccak(RLP::hexStringToByteArray(keccak(userAddr.toString() + RLP::hexStringToByteArray(keccak(tokenAddr.toString() + pos.toString())).toString())).toString()));
    Proof balanceProof = Proof(key, path, tokenAddr, userAddr);

    return std::make_pair(accoutProof, balanceProof);
};

Account RLP::decodeAccount(ByteArray input) {
    std::vector<ByteArray> elements = decodeList(input);
    ByteArray _nonce = remove_length(elements[0]);
    unsigned int nonce = 0;
    for (int i = 0; i < _nonce.data.size(); i++) {
        nonce = nonce * 256 + _nonce.data[i];
    }
    ByteArray _balance = remove_length(elements[1]);
    uint256_t balance = 0;
    for (int i = 0; i < _balance.data.size(); i++) {
        balance = balance * 256 + _balance.data[i];
    }
    ByteArray rootHash = remove_length(elements[2]);
    ByteArray codeHash = remove_length(elements[3]);
    return Account(nonce, balance, rootHash, codeHash);
}

std::vector<ByteArray> RLP::decodeList(ByteArray input) {
    int pos = 0, len = decodeLength(input, pos);
    int end = len + pos;
    std::vector<ByteArray> ret;
    int pre = pos;
    while (pos < end) {
        int now = decodeLength(input, pos);
        ret.push_back(input.substr(pre, pos + now));
        pos += now;
        pre = pos;
    }
    return ret;
}

ByteArray RLP::remove_length(ByteArray input) {
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