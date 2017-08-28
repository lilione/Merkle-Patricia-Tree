#include <iostream>
#include <vector>
#include "src/RLP.h"
#include "src/Node.h"
#include "src/Keccak.h"

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

void test_keccak() {
    std::string st = "123456";
    Keccak keccak;
    std::string res = keccak(st);
    std::cout << res << std::endl;
}

int removeFlag(std::string encodedPath, std::string path, int pathPtr) {
    if (encodedPath[0] == '0' || encodedPath[0] == '2') {
        encodedPath = encodedPath.substr(2);
    }
    else {
        encodedPath = encodedPath.substr(1);
    }
    if (encodedPath == path.substr(pathPtr, encodedPath.length())) {
        return encodedPath.length();
    }
    printf("encodedPath != path.substr(pathPtr, encodedPath.length())");
    return -1;
}

void output(std::string st) {
    for (int i = 0; i < st.length(); i++) {
        printf("%02x ", (unsigned char)st.c_str()[i]);
    }
    printf("\n");
}

void output(std::vector<std::string> list) {
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << std::endl;
    }
}

bool verifyProof(std::string path, TX tx, std::vector<Node> parentNodes, std::string rootHash) {
    RLP rlp;
    Keccak keccak;
    std::string nodeKey = rootHash;
    int pathPtr = 0;
    for (int i = 0; i < parentNodes.size(); i++) {
        //return 1 : parentNodes.size() ?= i
        Node currentNode = parentNodes[i];
        if (nodeKey != keccak(rlp.encode(currentNode.content))) {
            printf("nodeKey != keccak(rlp.encode(currentNode.content))\n");
            return 0;
        }
        if (pathPtr > path.length()) {
            printf("pathPtr >= path.length()");
            return 0;
        }
        switch(currentNode.content.size()) {
            case 17:
                if (pathPtr == path.length()) {
                    if (rlp.hexToBin(rlp.removeHexFormat(currentNode.content[16])) == rlp.encode(tx)) {
                        return 1;
                    } else {
                        printf("currentNode.content[16] == rlp.encode(tx)]\n");
                        return 0;
                    }
                }
                nodeKey = currentNode.content[rlp.charToInt(path[pathPtr])];
                pathPtr += 1;
                break;
            case 2:
                pathPtr += removeFlag(currentNode.content[0], path, pathPtr);
                if (pathPtr == path.length()) {
                    if (rlp.hexToBin(rlp.removeHexFormat(currentNode.content[1])) == rlp.encode(tx)) {
                        return 1;
                    }
                    printf("not found leaf node\n");
                    return 0;
                }
                else {
                    nodeKey = currentNode.content[1];
                }
                break;
            default:
                printf("all nodes must be length 17 or 2\n");
                return 0;
        }
    }
    return 0;
}

std::string read_string() {
    char st[1000000];
    gets(st);
    std::string ret = "";
    for (int i = 0; i < strlen(st); i++) {
        if (st[i] != ' ') ret += st[i];
    }
    return ret;
}

void read() {
    RLP rlp;
    freopen("../input.txt", "r", stdin);
    char st[100];

    //path
    std::string path = read_string();

    //value
    TX tx;
    tx.nonce = read_string();
    tx.gasPrice = read_string();
    tx.startGas = read_string();
    tx.to = read_string();
    tx.value = read_string();
    tx.data = read_string();
    tx.v = read_string();
    tx.r = read_string();
    tx.s = read_string();

    //parentNodes
    int n;
    scanf("%d", &n);
    std::vector<Node> parentNodes;
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        gets(st);
        Node node;
        for (int j = 0; j < m; j++) {
            std::string tmp = read_string();
            node.content.push_back(tmp);
        }
        parentNodes.push_back(node);
    }

    //rootHash
    std::string rootHash = read_string();

    if (verifyProof(path, tx, parentNodes, rootHash)) {
        printf("Success!\n");
    }
    else {
        printf("Failed!\n");
    }
    fclose(stdin);
}

int main() {
    //test_rlp();
    //test_keccak();
    read();
    return 0;
}