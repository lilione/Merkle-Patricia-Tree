#include <iostream>

#include "src/RLP.h"
#include "src/Utils.h"
#include "src/Inf.h"

int main() {
    freopen("../data/inputProof.txt", "r", stdin);
    Inf::getInf();
    fclose(stdin);

    freopen("../data/inputHeader.txt", "r", stdin);
    Bytes bytes = Utils::readHexString();
    Header header = RLP::decodeHeader(bytes);
    bytes = Utils::readHexString();
    Header parentHeader = RLP::decodeHeader(bytes);
    Header::check(header, parentHeader) ? printf("Header Validation Success!\n") : printf("Header Validation Failed!\n");
    fclose(stdin);
}