#include <iostream>
#include <vector>
#include "src/RLP.h"
#include "src/Node.h"
#include "src/Keccak.h"
#define CATCH_CONFIG_MAIN
#include "src/catch.cpp"
#include "src/Proof.h"

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

bool verifyProof(std::string path, std::vector<ByteArray> tx, std::vector<Node> parentNodes, std::string rootHash) {
    RLP rlp;
    Keccak keccak;
    std::string nodeKey = rootHash;
    int pathPtr = 0;
    for (int i = 0; i < parentNodes.size(); i++) {
        Node currentNode = parentNodes[i];
        if (nodeKey != keccak(rlp.toString(rlp.encode(currentNode.content)))) {
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
                    if (currentNode.content[16] == rlp.encode(tx)) {
                        return 1;
                    } else {
                        printf("currentNode.content[16] == rlp.encode(tx)]\n");
                        return 0;
                    }
                }
                nodeKey = rlp.binToHex(currentNode.content[rlp.charToInt(path[pathPtr])]);
                pathPtr += 1;
                break;
            case 2:
                pathPtr += removeFlag(rlp.binToHex(currentNode.content[0]), path, pathPtr);
                if (pathPtr == path.length()) {
                    if (currentNode.content[1] == rlp.encode(tx)) {
                        return 1;
                    }
                    printf("not found leaf node\n");
                    return 0;
                }
                else {
                    nodeKey = rlp.binToHex(currentNode.content[1]);
                }
                break;
            default:
                printf("all nodes must be length 17 or 2\n");
                return 0;
        }
    }
}

ByteArray read_string() {
    char st[1000000];
    gets(st);
    std::string ret = "";
    for (int i = 0; i < strlen(st); i++) {
        if (st[i] != ' ') ret += st[i];
    }
    RLP rlp;
    return rlp.hexToBin(ret);
}

bool read() {
    RLP rlp;
    char st[100];
    gets(st);
    gets(st);

    //path
    ByteArray path = read_string();

    //tx
    std::vector<ByteArray> tx;
    for (int i = 0; i < 9; i++) {
        tx.push_back(read_string());
    }

    //parentNodes
    std::vector<Node> parentNodes;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Node node;
        int m;
        scanf("%d", &m);
        gets(st);
        for (int j = 0; j < m; j++) {
            node.content.push_back(read_string());
        }
        parentNodes.push_back(node);
    }

    //rootHash
    ByteArray rootHash = read_string();

    //encode
    std::vector<ByteArray> list;
    list.push_back(rlp.encode(path));
    list.push_back(rlp.encode(tx));
    std::vector<ByteArray> nodes;
    for (int i = 0; i < parentNodes.size(); i++) {
        nodes.push_back(rlp.encode(parentNodes[i].content));
    }
    list.push_back(rlp.encode(nodes));
    list.push_back(rlp.encode(rootHash));

    ByteArray encoded = rlp.encode(list);

    Proof proof = rlp.decode(encoded);

    if (verifyProof(rlp.binToHex(proof.path), proof.tx, proof.parentNodes, rlp.binToHex(proof.rootHash))) {
        printf("Success!\n");
        return 1;
    }
    else {
        printf("Failed!\n");
        return 0;
    }
}

TEST_CASE("test") {
    SECTION("verification") {
        freopen("../data/input1.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input2.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input3.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input4.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input5.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input6.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input7.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input8.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input9.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input10.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input11.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input12.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input13.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
    SECTION("verification") {
        freopen("../data/input14.txt", "r", stdin);
        REQUIRE( read() == true );
        fclose(stdin);
    }
}