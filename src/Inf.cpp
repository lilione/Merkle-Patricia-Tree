//
// Created by lilione on 2017/10/12.
//

#include "Inf.h"
#include "Keccak.h"
#include "Utils.h"
#include "Proof.h"
#include "RLP.h"
#include "Transform.h"

Inf Inf::getInf(const Queue& queue) {
    Keccak keccak;

    Bytes encoded = Utils::readHexString();

    auto proofs = RLP::decodeProof(encoded);

    Proof accoutProof = proofs.first, balanceProof = proofs.second;

    ethash_h256_t accountRootHash = queue.getLast().stateRoot;

    auto ret = Proof::verifyProof(Transform::bytesToHexString(accoutProof.key), accoutProof.path, accountRootHash);

    if (!ret.second) {
        printf("accountProof Failed!\n");
        return Inf();
    }
    printf("accountProof Success!\n");

    Account account = RLP::decodeAccount(ret.first);
    ethash_h256_t balanceRootHash = account.rootHash;

    ret = Proof::verifyProof(Transform::bytesToHexString(balanceProof.key), balanceProof.path, balanceRootHash);

    if (!ret.second) {
        printf("balanceProof Failed!\n");
        return Inf();
    }
    printf("balanceProof Success!\n");

    Bytes _balance = RLP::remove_length(ret.first);
    uint256_t balance = Transform::bytesToUint256(_balance);

    return Inf(balanceProof.pos, balanceProof.tokenAddr, balanceProof.userAddr, balance);
}
