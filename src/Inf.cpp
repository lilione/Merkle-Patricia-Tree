//
// Created by lilione on 2017/10/12.
//

#include "Inf.h"
#include "Keccak.h"
#include "Utils.h"
#include "Proof.h"
#include "RLP.h"
#include "Transform.h"

Inf Inf::getInf() {
    Keccak keccak;

    Bytes encoded = Utils::readHexString();

    auto proofs = RLP::decodeProof(encoded);

    Proof accoutProof = proofs.first, balanceProof = proofs.second;

    Bytes accountRootHash = keccak(RLP::encodeList(accoutProof.path[0].content));

    auto ret = Proof::verifyProof(Transform::bytesToHexString(accoutProof.key), accoutProof.path, accountRootHash);

    if (!ret.second) {
        printf("accountProof Failed!\n");
        return Inf();
    }
    printf("accountProof Success!\n");

    Account account = RLP::decodeAccount(ret.first);
    Bytes balanceRootHash = account.rootHash;

    ret = Proof::verifyProof(Transform::bytesToHexString(balanceProof.key), balanceProof.path, balanceRootHash);

    if (!ret.second) {
        printf("balanceProof Failed!\n");
        return Inf();
    }
    printf("balanceProof Success!\n");

    Bytes _balance = RLP::remove_length(ret.first);
    uint256_t balance = 0;
    for (int i = 0; i < _balance.data.size(); i++) {
        balance = balance * 256 + _balance.data[i];
    }

    return Inf(balanceProof.pos, balanceProof.tokenAddr, balanceProof.userAddr, balance);
}
