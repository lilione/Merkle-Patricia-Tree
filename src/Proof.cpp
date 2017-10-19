//
// Created by lilione on 2017/8/29.
//

#include <iostream>

#include "Proof.h"
#include "Keccak.h"
#include "RLP.h"
#include "Transform.h"
#include "Utils.h"

void Proof::output(Proof proof) {
    printf("key is ");
    for (int k = 0; k < proof.key.data.size(); k++) {
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
    }
}

int Proof::removeFlag(std::string encodedPath, std::string key, int keyPos) {
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

std::pair<Bytes, bool> Proof::verifyProof(std::string key, std::vector<Node> proof, ethash_h256_t rootHash) {
    Keccak keccak;
    ethash_h256_t wantHash = rootHash;
    int keyPos = 0;
    for (int i = 0; i < proof.size(); i++) {
        Node currentNode = proof[i];
        if (!Utils::equal(wantHash, Transform::bytesToHash(keccak(RLP::encodeList(currentNode.content))))) {
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
                        return std::make_pair(RLP::remove_length(currentNode.content[16]), true);
                    else
                        return std::make_pair(Bytes(), false);
                }
                wantHash = Transform::bytesToHash(RLP::remove_length(currentNode.content[Transform::fromHex(key[keyPos])]));
                keyPos += 1;
                break;
            }
            case 2: {
                int offset = removeFlag(Transform::bytesToHexString(RLP::remove_length(currentNode.content[0])), key, keyPos);
                if (offset == -1)
                    return std::make_pair(Bytes(), false);
                keyPos += offset;
                if (keyPos == key.length()) {
                    if (i == proof.size() - 1) {
                        return std::make_pair(RLP::remove_length(currentNode.content[1]), true);
                    }
                    return std::make_pair(Bytes(), false);
                } else {
                    wantHash = Transform::bytesToHash(RLP::remove_length(currentNode.content[1]));
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