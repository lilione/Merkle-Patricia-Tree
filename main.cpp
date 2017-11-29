#include <iostream>
#include <cstdio>

#include "src/RLP.h"
#include "src/Utils.h"
#include "src/Inf.h"
#include "src/ReceiptProof.h"
#include "src/Transform.h"
#include "src/Keccak.h"

int main() {
    Keccak keccak;
    Bytes bytes;

    freopen("../data/inputReceipt.txt", "r", stdin);
    bytes = Utils::readHexString();
    ReceiptProof receiptProof = RLP::decodeReceiptProof(bytes);
    ethash_h256_t receiptRootHash = Transform::bytesToHash(keccak(RLP::encodeList(receiptProof.path[0].content)));

    //ethash_h256_t accountRootHash = queue.getLast().stateRoot;
    auto ret = Proof::verifyProof(Transform::bytesToHexString(receiptProof.key), receiptProof.path, receiptRootHash);

    if (!ret.second) {
        printf("receiptProof Failed!\n");
    }
    else {
        printf("receiptProof Success!\n");
    }
    RLP::decodeReceipt(ret.first);
    fclose(stdin);

    /*freopen("../data/inputProof.txt", "r", stdin);
    //Inf inf = Inf::getInf(queue);
    Inf inf = Inf::getInf();
    std::cout<<inf.pos<<std::endl;
    Address::outputHex(inf.tokenAddr);
    Address::outputHex(inf.userAddr);
    std::cout<<inf.value<<std::endl;
    fclose(stdin);*/

    /*Queue queue;
    freopen("../data/inputHeader.txt", "r", stdin);
    bytes = Utils::readHexString();
    Header header1 = RLP::decodeHeader(bytes);
    queue.addNewHeader(header1);
    printf("parentHeader in queue!\n");
    bytes = Utils::readHexString();
    Header header2 = RLP::decodeHeader(bytes);
    queue.addNewHeader(header2);
    printf("currentHeader in queue!\n");
    fclose(stdin);*/
}