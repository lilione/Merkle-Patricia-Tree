//
// Created by lilione on 2017/9/21.
//

#ifndef POW_UTILS_H
#define POW_UTILS_H

#include <string>

#include "../libethash/ethash.h"
#include "uint256_t.h"
#include "Bytes.h"

using byte = uint8_t;
using bytes = std::vector<byte>;

class Utils {
public:
    static bool equal(ethash_h256_t x, ethash_h256_t y);

    static uint256_t power(uint256_t, uint256_t);

    static uint256_t min(uint256_t x, uint256_t y);

    static uint256_t max(uint256_t x, uint256_t y);

    static Bytes readHexString();

    static void outputHex(ethash_h256_t);
};


#endif //POW_UTILS_H
