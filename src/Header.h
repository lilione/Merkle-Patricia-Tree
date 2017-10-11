//
// Created by lilione on 2017/9/20.
//

#ifndef POW_HEADER_H
#define POW_HEADER_H

#include <string>

#include "../libethash/ethash.h"
#include "uint256_t.h"

class Header {
public:
    uint256_t blockNumber, difficulty, timestamp, gasLimit, gasUsed;
    ethash_h256_t minerHash, difficultyAfterDivide, mixHash;
    uint64_t nonce;
    std::string extraData;

    Header() {}

    Header(uint256_t blockNumber,
           uint64_t nonce,
           uint256_t difficulty,
           uint256_t timestamp,
           uint256_t gasLimit,
           uint256_t gasUsed,
           ethash_h256_t minerHash,
           ethash_h256_t difficultyAfterDivide,
           ethash_h256_t mixHash,
           std::string extraData) :
            blockNumber(blockNumber),
            nonce(nonce),
            difficulty(difficulty),
            timestamp(timestamp),
            gasLimit(gasLimit),
            gasUsed(gasUsed),
            minerHash(minerHash),
            difficultyAfterDivide(difficultyAfterDivide),
            mixHash(mixHash),
            extraData(extraData) {}

    static Header readHeader();

    static bool check(Header header, Header parentHeader);

};
#endif //POW_HEADER_H
