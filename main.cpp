#include <iostream>
#include <cstdio>

#include "src/RLP.h"
#include "src/Utils.h"
#include "src/Inf.h"

int main() {
    Queue queue;
    freopen("../data/inputHeader.txt", "r", stdin);
    Bytes bytes;
    bytes = Utils::readHexString();
    Header header1 = RLP::decodeHeader(bytes);
    queue.addNewHeader(header1);
    printf("parentHeader in queue!\n");
    bytes = Utils::readHexString();
    Header header2 = RLP::decodeHeader(bytes);
    queue.addNewHeader(header2);
    printf("currentHeader in queue!\n");
    fclose(stdin);

    freopen("../data/inputProof.txt", "r", stdin);
    Inf inf = Inf::getInf(queue);
    std::cout<<inf.pos<<std::endl;
    Address::outputHex(inf.tokenAddr);
    Address::outputHex(inf.userAddr);
    std::cout<<inf.value<<std::endl;
    fclose(stdin);
}