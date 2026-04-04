#include "testFunctions.h"
#include "binHeap.h"
#include "priorityQueue.h"
#include <iostream>

void testBinHeap() {
    BinHeap bh;

    bh.insert(10);
    bh.insert(20);
    bh.insert(5);
    bh.insert(15);

    std::cout << "Heap elements: ";
    bh.display(); // Should display the heap in level order

    int* sortedArray = bh.heapSort();
    std::cout << "Sorted elements: ";
    for (int i = 0; i < bh.getSize(); i++) {
        std::cout << sortedArray[i] << " ";
    }
    std::cout << std::endl;

    delete[] sortedArray; // Clean up the sorted array
}

void testPriorityQueue() {
    priorityQueue pq;

    pq.enqueue(10);
    pq.enqueue(20);
    pq.enqueue(5);
    pq.enqueue(15);

    std::cout << "Maximum element: " << pq.maximum() << std::endl; // Should print 20

    std::cout << "Dequeue maximum element: " << pq.dequeue() << std::endl; // Should print 20
    std::cout << "New maximum element: " << pq.maximum() << std::endl; // Should print 15

}
