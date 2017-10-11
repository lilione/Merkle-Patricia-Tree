#include <iostream>
#include <vector>

#include "src/RLP.h"
#include "src/Node.h"
#include "src/Keccak.h"
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

std::pair<ByteArray, bool> verifyProof(std::string key, std::vector<Node> proof, ByteArray rootHash) {
    RLP rlp;
    Keccak keccak;
    ByteArray wantHash = rootHash;
    int keyPos = 0;
    for (int i = 0; i < proof.size(); i++) {
        Node currentNode = proof[i];
        if (wantHash != keccak(rlp.encodeList(currentNode.content))) {
            printf("wantHash != keccak(rlp.encodeList(currentNode.content))\n");
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
                        return std::make_pair(rlp.remove_length(currentNode.content[16]), true);
                    else
                        return std::make_pair(ByteArray(), false);
                }
                wantHash = rlp.remove_length(currentNode.content[rlp.charToInt(key[keyPos])]);
                keyPos += 1;
                break;
            }
            case 2: {
                int offset = removeFlag(rlp.byteArrayToHexString(rlp.remove_length(currentNode.content[0])), key, keyPos);
                if (offset == -1)
                    return std::make_pair(ByteArray(), false);
                keyPos += offset;
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1) {
                        return std::make_pair(rlp.remove_length(currentNode.content[1]), true);
                    }
                    return std::make_pair(ByteArray(), false);
                } else {
                    wantHash = rlp.remove_length(currentNode.content[1]);
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
    Keccak keccak;

    ByteArray encoded = read_string();

    auto proofs = rlp.decodeProof(encoded);

    Proof accoutProof = proofs.first, balanceProof = proofs.second;

    ByteArray accountRootHash = keccak(rlp.encodeList(accoutProof.path[0].content));

    auto ret = verifyProof(rlp.byteArrayToHexString(accoutProof.key), accoutProof.path, accountRootHash);

    if (!ret.second) {
        printf("accountProof Failed!\n");
        return 0;
    }
    printf("accountProof Success!\n");

    Account account = rlp.decodeAccount(ret.first);
    ByteArray balanceRootHash = account.rootHash;

    ret = verifyProof(rlp.byteArrayToHexString(balanceProof.key), balanceProof.path, balanceRootHash);

    if (!ret.second) {
        printf("balanceProof Failed!\n");
        return 0;
    }
    printf("balanceProof Success!\n");

    ByteArray _balance = rlp.remove_length(ret.first);
    uint256_t balance = 0;
    for (int i = 0; i < _balance.data.size(); i++) {
        balance = balance * 256 + _balance.data[i];
    }

    return 1;
}

int main() {
    freopen("../data/input.txt", "r", stdin);
    read();
    fclose(stdin);
}