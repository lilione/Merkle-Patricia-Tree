//
// Created by lilione on 2017/8/23.
//

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include "RLP.h"
#include "Keccak.h"
#include "Transform.h"

const int offset_string = 128;
const int offset_list = 192;

Bytes RLP::encodeString(Bytes input) {
    if (input.data.size() == 1 && input.data[0] < 128) {
        return input;
    }
    return encodeLength(input.data.size(), 128) + input;
}

Bytes RLP::encodeList(std::vector<Bytes> list) {
    Bytes ret;
    for (int i = 0; i < list.size(); i++) {
        ret = ret + list[i];
    }
    return encodeLength(ret.data.size(), 192) + ret;
}

Bytes RLP::encodeLength(int L, int offset) {
    //len should be less than 256**8
    if (L < 56) {
        return Bytes(L + offset);
    }
    Bytes BL = intToByteArray(L);
    return Bytes(BL.data.size() + offset + 55) + BL;
}

Bytes RLP::intToByteArray(int x) {
    Bytes ret;
    if (x != 0) {
        ret = intToByteArray(x / 256) + Bytes(x % 256);
    }
    return ret;
}

Bytes RLP::hexStringToByteArray(std::string st) {
    //must of even length
    Bytes ret;
    for (int i = 0; i < st.length(); i += 2) {
        ret = ret + Bytes(charToInt(st[i]) * 16 + charToInt(st[i + 1]));
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

std::string RLP::byteArrayToHexString(Bytes array) {
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

std::pair<Proof, Proof> RLP::decodeProof(Bytes input) {
    Keccak keccak;
    RLP rlp;

    std::vector<Bytes> elements = decodeList(input);
    std::vector<Bytes> path_list = decodeList(elements[0]);
    std::vector<Node> path;
    for (int i = 0; i < path_list.size(); i++) {
        path.push_back(Node(decodeList(path_list[i])));
    }
    Bytes key = keccak(remove_length(elements[1]));
    Proof accoutProof = Proof(key, path);

    path_list = decodeList(elements[2]);
    path.clear();
    for (int i = 0; i < path_list.size(); i++) {
        path.push_back(Node(decodeList(path_list[i])));
    }

    Bytes userAddr = remove_length(elements[3]);
    Bytes tokenAddr = remove_length(elements[4]);
    Bytes pos = remove_length(elements[5]);

    key = keccak(keccak(userAddr + keccak(tokenAddr + pos)));

    Proof balanceProof = Proof(key, path, tokenAddr, userAddr);

    return std::make_pair(accoutProof, balanceProof);
};

Account RLP::decodeAccount(Bytes input) {
    std::vector<Bytes> elements = decodeList(input);
    Bytes _nonce = remove_length(elements[0]);
    unsigned int nonce = 0;
    for (int i = 0; i < _nonce.data.size(); i++) {
        nonce = nonce * 256 + _nonce.data[i];
    }
    Bytes _balance = remove_length(elements[1]);
    uint256_t balance = 0;
    for (int i = 0; i < _balance.data.size(); i++) {
        balance = balance * 256 + _balance.data[i];
    }
    Bytes rootHash = remove_length(elements[2]);
    Bytes codeHash = remove_length(elements[3]);
    return Account(nonce, balance, rootHash, codeHash);
}

std::vector<Bytes> RLP::decodeList(Bytes input) {
    int pos = 0, len = decodeLength(input, pos);
    int end = len + pos;
    std::vector<Bytes> ret;
    int pre = pos;
    while (pos < end) {
        int now = decodeLength(input, pos);
        ret.push_back(input.substr(pre, pos + now));
        pos += now;
        pre = pos;
    }
    return ret;
}

Bytes RLP::remove_length(Bytes input) {
    int pos = 0, len = decodeLength(input, pos);
    return input.substr(pos, pos + len);
}

int RLP::decodeLength(Bytes input, int& pos) {
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