//
// Created by lilione on 2017/10/11.
//

#include <string>
#include <sstream>

#include "Transform.h"
#include "Bytes.h"
#include "uint256_t.h"

int Transform::fromHex(char _i) {
    if (isdigit(_i))
        return _i - '0';
    if (islower(_i))
        return _i - 'a' + 10;
    if (isupper(_i))
        return _i - 'A' + 10;

    static_assert("should never get here");
    return -1;
}

char Transform::toHex(int _i) {
    if (_i < 10) return _i + '0';
    if (_i < 16) return _i - 10 + 'a';

    static_assert("should never get here");
    return -1;
}

Bytes Transform::stringToBytes(std::string st) {
    Bytes ret;
    for (int i = 0; i < st.length(); i++) {
        ret.data.push_back(uint8_t(st[i]));
    }
    return ret;
}

Bytes Transform::hexStringToBytes(std::string st) {
    uint pos = (st[0] == '0' && st[1] == 'x') ? 2 : 0;
    Bytes ret;
    ret.data.reserve((st.size() - pos + 1) / 2);

    if (st.size() % 2) {
        ret.data.push_back(fromHex(st[pos++]));
    }
    for (uint i = pos; i < st.size(); i += 2) {
        ret.data.push_back((byte)(fromHex(st[i]) * 16 + fromHex(st[i + 1])));
    }

    return ret;
}

std::string Transform::bytesToString(Bytes bytes) {
    std::string st;
    for (int i = 0; i < bytes.data.size(); i++) {
        st += char(bytes.data[i]);
    }
    return st;
}

uint256_t Transform::intStringToUint256_t(std::string st) {
    uint256_t ret = 0;
    for (int i = 0; i < st.length(); i++) {
        ret *= 10;
        ret += st[i] - '0';
    }
    return ret;
}

ethash_h256_t Transform::hexStringToHash(std::string st) {
    ethash_h256_t ret;
    Bytes b = hexStringToBytes(st);
    memcpy(&ret, b.data.data(), b.data.size());
    return ret;
}

uint256_t Transform::hexStringToUint256_t(std::string st) {
    uint256_t ret = 0;

    if (st[0] == '0' && st[1] == 'x') {
        st = st.substr(2);
    }

    for (int i = 0; i < st.length(); i++) {
        ret = ret * 16 + fromHex(st[i]);
    }

    return ret;
}

ethash_h256_t Transform::uint256_tToHash(uint256_t x) {
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

Bytes Transform::intToBytes(int x) {
    Bytes ret;
    if (x != 0) {
        ret = intToBytes(x / 256) + Bytes(x % 256);
    }
    return ret;
}

std::string Transform::bytesToHexString(Bytes array) {
    std::string ret;
    for (int i = 0; i < array.data.size(); i++) {
        int now = array.data[i];
        ret += toHex(now / 16);
        ret += toHex(now % 16);
    }
    return ret;
}
