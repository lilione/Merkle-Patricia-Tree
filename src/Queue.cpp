//
// Created by lilione on 2017/10/9.
//

#include "Queue.h"

bool Queue::addNewHeader(const Header& header) {
    if (headers.empty() || Header::check(header, headers.back())) {
        while (headers.size() >= QUEUE_LENGTH) {
            headers.pop_front();
        }
        headers.push_back(header);
        return true;
    }
    return false;
}

Header Queue::getLast() {
    return headers.back();
}

unsigned int Queue::getLength() {
    return headers.size();
}
