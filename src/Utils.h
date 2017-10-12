//
// Created by lilione on 2017/9/21.
//

#ifndef POW_UTILS_H
#define POW_UTILS_H

#include <string>

#include "../libethash/ethash.h"
#include "uint256_t.h"

using byte = uint8_t;
using bytes = std::vector<byte>;

class Utils {
public:
    //static void output(ethash_h256_t x);

    //static ethash_h256_t stringToBlockhash(std::string const &_s);

    //static int fromHex(char _i);

    //static char toHex(int _i);

    //static bytes hexStringToBytes(std::string const &_s);

    //static uint64_t hexStringToUint64_t(std::string const &_s);

    //static ethash_h256_t stringToEthash_h256_t(std::string const &_s);

    static ethash_h256_t uint256_tToEthash_h256_t(uint256_t);

    static bool equal(ethash_h256_t x, ethash_h256_t y);

    //static uint256_t hexStringToUint256_t(std::string);

    //static uint256_t uint64_tToUint256_t(uint64_t);

    static uint256_t power(uint256_t, uint256_t);

    static uint256_t min(uint256_t x, uint256_t y);

    static uint256_t max(uint256_t x, uint256_t y);

    static int min_int(int x, int y);

    static int max_int(int x, int y);
};


#endif //POW_UTILS_H
