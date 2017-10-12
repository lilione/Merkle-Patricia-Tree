//
// Created by lilione on 2017/10/9.
//

#ifndef POW_QUEUE_H
#define POW_QUEUE_H

#include <deque>

#include "Header.h"

const unsigned int QUEUE_LENGTH = 50;

class Queue {
private:
    std::deque<Header> headers;

public:
    bool addNewHeader(const Header& header);
    Header getLast();
    unsigned int getLength();
};


#endif //POW_QUEUE_H
