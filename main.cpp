#include <iostream>
#include <vector>

#include "src/RLP.h"
#include "src/Node.h"
#include "src/Keccak.h"
#include "src/Proof.h"
#include "src/Header.h"
#include "src/Transform.h"

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

std::pair<Bytes, bool> verifyProof(std::string key, std::vector<Node> proof, Bytes rootHash) {
    RLP rlp;
    Keccak keccak;
    Bytes wantHash = rootHash;
    int keyPos = 0;
    for (int i = 0; i < proof.size(); i++) {
        Node currentNode = proof[i];
        if (wantHash != keccak(rlp.encodeList(currentNode.content))) {
            printf("wantHash != keccak(rlp.encodeList(currentNode.content))\n");
            return std::make_pair(Bytes(), false);
        }
        if (keyPos > key.length()) {
            printf("keyPos > key.length()");
            return std::make_pair(Bytes(), false);;
        }
        switch(currentNode.content.size()) {
            case 17: {
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1)
                        return std::make_pair(rlp.remove_length(currentNode.content[16]), true);
                    else
                        return std::make_pair(Bytes(), false);
                }
                wantHash = rlp.remove_length(currentNode.content[Transform::fromHex(key[keyPos])]);
                keyPos += 1;
                break;
            }
            case 2: {
                int offset = removeFlag(Transform::bytesToHexString(rlp.remove_length(currentNode.content[0])), key, keyPos);
                if (offset == -1)
                    return std::make_pair(Bytes(), false);
                keyPos += offset;
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1) {
                        return std::make_pair(rlp.remove_length(currentNode.content[1]), true);
                    }
                    return std::make_pair(Bytes(), false);
                } else {
                    wantHash = rlp.remove_length(currentNode.content[1]);
                }
                break;
            }
            default: {
                printf("all nodes must be length 17 or 2\n");
                return std::make_pair(Bytes(), false);
            }
        }
    }
    printf("Length of Proof is not enough\n");
    return std::make_pair(Bytes(), false);
}

Bytes read_string() {
    char st[1000000];
    gets(st);
    std::string ret = "";
    for (int i = 0; i < strlen(st); i++) {
        if (st[i] != ' ') ret += st[i];
    }
    return Transform::hexStringToBytes(ret);
}

bool read() {
    RLP rlp;
    Keccak keccak;

    Bytes encoded = read_string();

    auto proofs = rlp.decodeProof(encoded);

    Proof accoutProof = proofs.first, balanceProof = proofs.second;

    Bytes accountRootHash = keccak(rlp.encodeList(accoutProof.path[0].content));

    auto ret = verifyProof(Transform::bytesToHexString(accoutProof.key), accoutProof.path, accountRootHash);

    if (!ret.second) {
        printf("accountProof Failed!\n");
        return 0;
    }
    printf("accountProof Success!\n");

    Account account = rlp.decodeAccount(ret.first);
    Bytes balanceRootHash = account.rootHash;

    ret = verifyProof(Transform::bytesToHexString(balanceProof.key), balanceProof.path, balanceRootHash);

    if (!ret.second) {
        printf("balanceProof Failed!\n");
        return 0;
    }
    printf("balanceProof Success!\n");

    Bytes _balance = rlp.remove_length(ret.first);
    uint256_t balance = 0;
    for (int i = 0; i < _balance.data.size(); i++) {
        balance = balance * 256 + _balance.data[i];
    }

    return 1;
}

int main() {
    freopen("../data/inputProof.txt", "r", stdin);
    read();
    fclose(stdin);

    freopen("../data/inputHeader.txt", "r", stdin);
    Header parentHeader = Header::readHeader();
    Header header = Header::readHeader();
    Header::check(header, parentHeader) ? printf("Header Validation Success!\n") : printf("Header Validation Failed!\n");
    fclose(stdin);
}