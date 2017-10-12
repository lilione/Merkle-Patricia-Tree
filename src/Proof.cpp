//
// Created by lilione on 2017/8/29.
//

#include <iostream>
#include "Proof.h"

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
