#include <iostream>
#include <vector>
#include "src/RLP.h"
#include "src/Node.h"
#include "src/Keccak.h"
//#define CATCH_CONFIG_MAIN

#include "src/catch.cpp"
#include "src/Proof.h"

int removeFlag(std::string encodedPath, std::string key, int keyPos) {
    if (encodedPath[0] == '0' || encodedPath[0] == '2') {
        encodedPath = encodedPath.substr(2);
    }
    else {
        encodedPath = encodedPath.substr(1);
    }
    if (encodedPath == key.substr(keyPos, encodedPath.length())) {
        return encodedPath.length();
    }
    printf("encodedPath != key.substr(keyPos, encodedPath.length())");
    return -1;
}

//bool verifyProof(std::string key, std::vector<ByteArray> tx, std::vector<Node> path, std::string rootHash) {
std::pair<ByteArray, bool> verifyProof(std::string key, std::vector<Node> proof, std::string rootHash) {
    RLP rlp;
    Keccak keccak;
    std::string wantHash = rootHash;
    int keyPos = 0;
    for (int i = 0; i < proof.size(); i++) {
        Node currentNode = proof[i];
        if (wantHash != keccak(rlp.encodeList(currentNode.content).toString())) {
            printf("wantHash != keccak(rlp.encode(currentNode.content))\n");
            return std::make_pair(ByteArray(), false);
        }
        if (keyPos > key.length()) {
            printf("keyPos > key.length()");
            return std::make_pair(ByteArray(), false);;
        }
        switch(currentNode.content.size()) {
            case 17: {
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1)
                        return std::make_pair(currentNode.content[16], true);
                    else
                        return std::make_pair(ByteArray(), false);
                }
                wantHash = rlp.byteArrayToHexString(rlp.remove_length(currentNode.content[rlp.charToInt(key[keyPos])]));
                keyPos += 1;
                break;
            }
            case 2: {
                int offset = removeFlag(rlp.byteArrayToHexString(rlp.remove_length(currentNode.content[0])), key, keyPos);
                if (offset == -1)
                    return std::make_pair(ByteArray(), false);
                keyPos += offset;
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1)
                        return std::make_pair(rlp.remove_length(currentNode.content[1]), true);
                    else
                        return std::make_pair(ByteArray(), false);
                } else {
                    wantHash = rlp.byteArrayToHexString(rlp.remove_length(currentNode.content[1]));
                }
                break;
            }
            default: {
                printf("all nodes must be length 17 or 2\n");
                return std::make_pair(ByteArray(), false);
            }
        }
    }
    printf("Length of Proof is not enough\n");
    return std::make_pair(ByteArray(), false);
}

ByteArray read_string() {
    char st[1000000];
    gets(st);
    std::string ret = "";
    for (int i = 0; i < strlen(st); i++) {
        if (st[i] != ' ') ret += st[i];
    }
    RLP rlp;
    return rlp.hexStringToByteArray(ret);
}

bool read() {
    RLP rlp;

    ByteArray rootHash = read_string();

    ByteArray encoded = read_string();

    Proof proof = rlp.decodeProof(encoded);

    /*for (int k = 0; k < proof.key.data.size(); k++) {
        printf("%d ", proof.key.data[k]);
    }
    printf("\n");

    std::cout << proof.path.size() << std::endl;
    for (int i = 0; i < proof.path.size(); i++) {
        Node now = proof.path[i];
        printf("node %d with %d branches\n", i, now.content.size());
        for (int j = 0; j < now.content.size(); j++) {
            for (int k = 0; k < now.content[j].data.size(); k++) {
                printf("%d ", now.content[j].data[k]);
            }
            printf("\n");
        }
    }*/

    Keccak keccak;

    auto ret = verifyProof(keccak(proof.key.toString()), proof.path, rlp.byteArrayToHexString(rootHash));
    if (ret.second) {
        printf("Success!\n");
        Account account = rlp.decodeAccount(ret.first);
        return 1;
    }
    else {
        printf("Failed!\n");
        return 0;
    }
}

/*
TEST_CASE("test") {
    /*SECTION("verification") {
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
    SECTION("verification") {
        printf("asdjfklas;fk");
        freopen("../data/input.txt", "r", stdin);
        REQUIRE( read());
        fclose(stdin);
    }
}*/

int main() {
    freopen("../data/input.txt", "r", stdin);
    read();
    fclose(stdin);
}