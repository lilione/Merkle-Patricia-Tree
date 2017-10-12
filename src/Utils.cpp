//
// Created by lilione on 2017/9/21.
//

#include <cstdio>
#include <vector>
#include <sstream>

#include "Utils.h"

bool Utils::equal(ethash_h256_t x, ethash_h256_t y) {
    for (int i = 0; i < 32; i++) {
        if (x.b[i] != y.b[i]) return false;
    };
    return true;
};

uint256_t Utils::power(uint256_t x, uint256_t y) {
    uint256_t ret = 1, z = x;
    while (y) {
        if (y & 1) ret *= z;
        z *= z;
        y >>= 1;
    }
    return ret;
}

uint256_t Utils::min(uint256_t x, uint256_t y) {
    return (x < y) ? x : y;
}

uint256_t Utils::max(uint256_t x, uint256_t y) {
    return (x > y) ? x : y;
}