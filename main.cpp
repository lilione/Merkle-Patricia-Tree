#include <iostream>
#include <vector>
#include "src/RLP.h"
#include "src/Node.h"

void test_rlp() {
    std::string st;
    //st = "0x0f";
    //st = "0x0400";
    st = "Lorem ipsum dolor sit amet, consectetur adipisicing elit";
    //st = "dog";
    //st = "";
    //std::vector<std::string> vec;
    //vec.push_back("cat");
    //vec.push_back("dog");
    RLP rlp;
    std::string res;
    //res = rlp.encode(rlp.hexToBin(rlp.removeHexFormat(st)));
    res = rlp.encode(st);
    //res = rlp.encode(vec);
    for (int i = 0; i < res.length(); i++) {
        if (isupper(res[i]) || islower(res[i])) printf("%c\n", res[i]);
        else printf("%02x\n", (unsigned char)res.c_str()[i]);
    }
}

bool verifyProof(std::string key, TX tx, std::vector<Node> path, std::string rootHash) {
    RLP rlp;
    std::string nodeKey = rootHash;
    for (int i = 0; i < path.size(); i++) {
        Node currentNode = path[i];
        if (nodeKey != rlp.encode(currentNode.content)) {

        }
    }
}

int main() {
    //test_rlp();
    return 0;
}