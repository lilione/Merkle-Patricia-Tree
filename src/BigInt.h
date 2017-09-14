//
// Created by lilione on 2017/9/13.
//

#ifndef MERKLE_PARTRICIA_TREE_BIGINT_H
#define MERKLE_PARTRICIA_TREE_BIGINT_H


#include <vector>
#include <string>

class BigInt {
public:
    std::vector<int> data;
    int base = 10;

    BigInt() {
        data.push_back(0);
    }

    BigInt(int x) {
        while (x) {
            data.push_back(x % base);
            x /= base;
        }
    }

    void deal() {
        int pos = 0;
        while (pos < data.size()) {
            if (data[pos] >= base) {
                if (pos < data.size() - 1) {
                    data[pos + 1] += data[pos] / base;
                } else {
                    data.push_back(data[pos] / base);
                }
                data[pos] %= base;
            }
            pos++;
        }
    }


    BigInt operator+ (const int& x) {
        BigInt ret = *this;
        ret.data[0] += x;
        ret.deal();
        return ret;
    }

    BigInt operator* (const int& x) {
        BigInt ret = *this;
        for (int i = 0; i < ret.data.size(); i++) {
            ret.data[i] *= x;
        }
        ret.deal();
        return ret;
    }

    std::string toString() {
        std::string ret = "";
        for (int i = data.size() - 1; i >= 0; i--) {
            ret += std::to_string(data[i]);
        }
        return ret;
    }
};


#endif //MERKLE_PARTRICIA_TREE_BIGINT_H
