//
// Created by lilione on 2017/9/20.
//

#include <cstdio>
#include <iostream>
#include <cmath>
#include <sys/param.h>
#include <sstream>
#include "Header.h"
#include "Utils.h"
#include "../libethash/internal.h"
#include "Transform.h"

uint256_t read_uint256_t() {
    char st[1000000];
    scanf("%s", st);

    return Transform::intStringToUint256_t(st);
}

ethash_h256_t read_hash() {
    char st[1000000];
    scanf("%s", st);

    return Transform::hexStringToHash(st);
}

std::string read_hexString() {
    char st[1000000];
    scanf("%s", st);

    return (st[0] == '0' && st[1] == 'x') ? std::string(st).substr(2) : st;
}

ethash_h256_t getDivide(uint256_t diff) {
    uint256_t TwoTo255 = Utils::power(2, 255);
    uint256_t _ret = TwoTo255 / diff * 2 + TwoTo255 % diff * 2 / diff;
    return Transform::uint256_tToHash(_ret);
}

Header Header::readHeader() {
    uint256_t blockNumber, difficulty, timestamp, gasLimit, gasUsed;
    ethash_h256_t minerHash, difficultyAfterDivide, mixHash;
    uint64_t nonce;
    std::string extraData;

    blockNumber = read_uint256_t();

    nonce = Transform::hexStringToUint256_t(read_hexString());

    difficulty = read_uint256_t();

    timestamp = read_uint256_t();

    gasLimit = read_uint256_t();

    gasUsed = read_uint256_t();

    minerHash = read_hash();

    mixHash = read_hash();

    difficultyAfterDivide = getDivide(difficulty);

    extraData = read_hexString();

    return Header(blockNumber, nonce, difficulty, timestamp, gasLimit, gasUsed, minerHash, difficultyAfterDivide, mixHash, extraData);
}

bool PoWCheck(Header header) {
    ethash_light_t light = ethash_light_new(header.blockNumber);
    if (!light) return false;
    ethash_return_value_t ret = ethash_light_compute(
            light,
            header.minerHash,
            header.nonce
    );
    if (!Utils::equal(ret.mix_hash, header.mixHash)) return false;
    if (!ethash_check_difficulty(&ret.result, &header.difficultyAfterDivide)) return false;
    ethash_light_delete(light);
    return true;
}

bool difficultyCheck(Header header, Header parentHeader) {
    const uint256_t D_0 = 131072, N_H = 1150000;
    uint256_t x = parentHeader.difficulty / 2048;
    uint256_t D_H = parentHeader.difficulty;
    if (header.blockNumber >= N_H) {
        uint256_t tmp = (header.timestamp - parentHeader.timestamp) / 10;
        if (tmp == 0) {
            D_H += x;
        }
        else {
            D_H -= x * Utils::min(tmp - 1, 99);
        }
    }
    else if (header.timestamp < parentHeader.timestamp + 13) {
        D_H += x;
    }
    else {
        D_H -= x;
    }
    uint256_t sigma = Utils::power(2, header.blockNumber / 100000 - 2);
    D_H += sigma;
    D_H = Utils::max(D_0, D_H);
    return header.difficulty == D_H;
}

bool gasCheck(Header header, Header parentHeader) {
    if (header.gasUsed > header.gasLimit) return false;
    uint256_t tmp = parentHeader.gasLimit / 1024;
    if (header.gasLimit > parentHeader.gasLimit + tmp) return false;
    if (header.gasLimit < parentHeader.gasLimit - tmp) return false;
    return header.gasLimit >= 125000;
}

bool timestampCheck(Header header, Header parentHeader) {
    return header.timestamp > parentHeader.timestamp;
}

bool blockNumberCheck(Header header, Header parentHeader) {
    return header.blockNumber == parentHeader.blockNumber + 1;
}

bool extraDataCheck(Header header) {
    return header.extraData.length() <= 64;
}

bool Header::check(Header header, Header parentHeader) {
    if (!PoWCheck(header)) {
        printf("PoWCheck failed!\n");
        return false;
    }
    if (!difficultyCheck(header, parentHeader)) {
        printf("difficultyCheck failed!\n");
        return false;
    }
    if (!gasCheck(header, parentHeader)) {
        printf("gasCheck failed!\n");
        return false;
    }
    if (!timestampCheck(header, parentHeader)) {
        printf("timestampCheck failed!\n");
        return false;
    }
    if (!blockNumberCheck(header, parentHeader)) {
        printf("blockNumberCheck failed!\n");
        return false;
    }
    if (!extraDataCheck(header)) {
        printf("extraDataCheck failed!\n");
        return false;
    }
    return true;
}
