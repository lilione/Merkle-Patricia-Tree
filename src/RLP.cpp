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
    Bytes BL = Transform::intToBytes(L);
    return Bytes(BL.data.size() + offset + 55) + BL;
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

    Proof balanceProof = Proof(key, path, pos, tokenAddr, userAddr);

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

Header RLP::decodeHeader(Bytes input) {
    std::vector<Bytes> elements = decodeList(input);
    ethash_h256_t parentHash = Transform::bytesToHash(remove_length(elements[0]));
    ethash_h256_t uncleHash = Transform::bytesToHash(remove_length(elements[1]));
    Address coinBase = Transform::bytesToAddr(remove_length(elements[2]));
    ethash_h256_t stateRoot = Transform::bytesToHash(remove_length(elements[3]));
    ethash_h256_t txRoot = Transform::bytesToHash(remove_length(elements[4]));
    ethash_h256_t receiptRoot = Transform::bytesToHash(remove_length(elements[5]));
    Bytes logsBloom = remove_length(elements[6]);
    uint256_t difficulty = Transform::bytesToUint256(remove_length(elements[7]));
    uint256_t number = Transform::bytesToUint256(remove_length(elements[8]));
    uint256_t gasLimit = Transform::bytesToUint256(remove_length(elements[9]));
    uint256_t gasUsed = Transform::bytesToUint256(remove_length(elements[10]));
    uint256_t timestamp = Transform::bytesToUint256(remove_length(elements[11]));
    Bytes extraData = remove_length(elements[12]);
    ethash_h256_t mixHash = Transform::bytesToHash(remove_length(elements[13]));
    uint64_t nonce = Transform::bytesToUint64(remove_length(elements[14]));

    return Header(parentHash, uncleHash,
                  coinBase,
                  stateRoot, txRoot, receiptRoot,
                  logsBloom,
                  difficulty, number, gasLimit, gasUsed, timestamp,
                  extraData,
                  mixHash,
                  nonce);
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