//
// Created by lilione on 2017/9/21.
//

#include <cstdio>
#include <vector>
#include <sstream>
#include "Utils.h"

/*void Utils::output(ethash_h256_t x) {
    for (int i = 0; i < 32; i++) {
        printf("%02x", x.b[i]);
    }
    printf("\n");
}*/

ethash_h256_t Utils::stringToBlockhash(std::string const& _s)
{
    ethash_h256_t ret;
    bytes b = hexStringToBytes(_s);
    memcpy(&ret, b.data(), b.size());
    return ret;
}

int Utils::fromHex(char _i)
{
    if (_i >= '0' && _i <= '9')
        return _i - '0';
    if (_i >= 'a' && _i <= 'f')
        return _i - 'a' + 10;
    if (_i >= 'A' && _i <= 'F')
        return _i - 'A' + 10;

    static_assert("should never get here");
    return -1;
}

/*char Utils::toHex(int _i) {
    if (_i < 10) return _i + '0';
    if (_i < 16) return _i + 'a';

    static_assert("should never get here");
    return -1;
}*/

bytes Utils::hexStringToBytes(std::string const& _s)
{
    unsigned s = (_s[0] == '0' && _s[1] == 'x') ? 2 : 0;
    std::vector<uint8_t> ret;
    ret.reserve((_s.size() - s + 1) / 2);

    if (_s.size() % 2)
        try
        {
            ret.push_back(fromHex(_s[s++]));
        }
        catch (...)
        {
            ret.push_back(0);
        }
    for (unsigned i = s; i < _s.size(); i += 2)
        try
        {
            ret.push_back((byte)(fromHex(_s[i]) * 16 + fromHex(_s[i + 1])));
        }
        catch (...){
            ret.push_back(0);
        }
    return ret;
}

/*uint64_t Utils::hexStringToUint64_t(std::string const& _s) {
    uint64_t ret = 0;
    std::string s = (_s[0] == '0' && _s[1] == 'x') ? _s.substr(2): _s;
    for (int i = 0; i < s.length(); i++) {
        ret = ret * 16 + fromHex(s[i]);
    }
    return ret;
}*/

/*ethash_h256_t Utils::stringToEthash_h256_t(std::string const& _s) {
    ethash_h256_t ret;
    std::string s = (_s[0] == '0' && _s[1] == 'x') ? _s.substr(2): _s;
    int cnt = 31;
    for (int i = s.length() - 1; i >= 0; i -= 2) {
        uint8_t tmp = fromHex(s[i]);
        if (i - 1 >= 0) {
            tmp += fromHex(s[i - 1]) * 16;
        }
        ret.b[cnt--] = tmp;
    }
    return ret;
}*/

ethash_h256_t Utils::uint256_tToEthash_h256_t(uint256_t x) {
    ethash_h256_t ret;
    int i;
    for (i = 0; x > 0; i++) {
        ret.b[32 - i - 1] = x % 256;
        x /= 256;
    }
    for (; i < 32; i++) {
        ret.b[32 - i - 1] = 0;
    }
    return ret;
}

bool Utils::equal(ethash_h256_t x, ethash_h256_t y) {
    for (int i = 0; i < 32; i++) {
        if (x.b[i] != y.b[i]) return false;
    };
    return true;
};

uint256_t Utils::hexStringToUint256_t(std::string st) {
    if (st[0] == '0' && st[1] == 'x') {
        st = st.substr(2);
    }

    uint64_t upper_lhs = 0, lower_lhs = 0, upper_rhs = 0, lower_rhs = 0;
    std::stringstream ss;

    ss << std::hex << st.substr(max_int(0, st.length() - 64), min_int(64, st.length()));
    ss >> lower_rhs;

    if (st.length() > 64) {
        ss << std::hex << st.substr(max_int(0, st.length() - 64 * 2), min_int(64, st.length() - 64));
        ss >> upper_rhs;
    }

    if (st.length() > 64 * 2) {
        ss << std::hex << st.substr(max_int(0, st.length() - 64 * 3), min_int(64, st.length() - 64 * 2));
        ss >> lower_lhs;
    }

    if (st.length() > 64 * 3) {
        ss << std::hex << st.substr(max_int(0, st.length() - 64 * 4), min_int(64, st.length() - 64 * 3));
        ss >> upper_lhs;
    }

    return uint256_t(upper_lhs, lower_lhs, upper_rhs, lower_rhs);
}

/*uint256_t Utils::uint64_tToUint256_t(uint64_t lower_rhs) {
    return uint256_t(0, 0, 0, lower_rhs);
}*/

uint256_t Utils::IntStringToUint256_t(std::string st) {
    uint256_t ret = 0;
    for (int i = 0; i < st.length(); i++) {
        ret *= 10;
        ret += st[i] - '0';
    }
    return ret;
}

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

int Utils::max_int(int x, int y) {
    return (x > y) ? x : y;
}

int Utils::min_int(int x, int y) {
    return (x < y) ? x : y;
}