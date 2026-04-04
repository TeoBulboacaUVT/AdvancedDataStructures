#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "binHeap.h"
#include <iostream>

// a priority queue implemented using a binary heap
class priorityQueue : public BinHeap {
public:
    priorityQueue() : BinHeap() {}

    //insert into the priority queue
    void enqueue(int value) {
        insert(value);
    }

    //return the maximum element without removing it from the priority queue
    int maximum() {
        if (isEmpty()) {
            std::cout << "Priority queue is empty." << std::endl;
            return -1;
        }
        return getNode(getRoot()); // return the maximum element (root of the heap)
    }

    //remove and return the maximum element from the priority queue
    int dequeue() {
        if (isEmpty()) {
            std::cout << "Priority queue is empty." << std::endl;
            return -1;
        }
        int max = getNode(getRoot()); // get the maximum element (root of the heap)
        removeMax();
        return max;
    }
};

#endif
