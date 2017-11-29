//
// Created by lilione on 2017/8/23.
//

#ifndef MERKLE_PARTRICIA_TREE_RLP_H
#define MERKLE_PARTRICIA_TREE_RLP_H

#include <cstdint>
#include <vector>

#include "Bytes.h"
#include "Proof.h"
#include "Account.h"
#include "Header.h"
#include "AccountProof.h"
#include "BalanceProof.h"
#include "ReceiptProof.h"

class RLP {
public:
    static Bytes encodeString(Bytes);
    static Bytes encodeList(std::vector<Bytes>);
    static Bytes encodeLength(int, int);

    static std::pair<AccountProof, BalanceProof> decodeDepositProof(Bytes);
    static Account decodeAccount(Bytes);
    static Header decodeHeader(Bytes);
    static ReceiptProof decodeReceiptProof(Bytes);
    static bool decodeReceipt(Bytes);

    static std::vector<Bytes> decodeList(Bytes);
    static Bytes remove_length(Bytes);
    static int decodeLength(Bytes, int&);
};

#endif //MERKLE_PARTRICIA_TREE_RLP_H
