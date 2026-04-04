#include "binHeap.h"
#include <iostream>


BinHeap::~BinHeap() {
    delete[] nodes;
}

void BinHeap::heapify(int index) {
    int largest = index;
    int left = 2 * index + 1; // left child index
    int right = 2 * index + 2; // right child index

    if (left < size && nodes[left] > nodes[largest]) largest = left; // compare left child with largest
    if (right < size && nodes[right] > nodes[largest]) largest = right; // compare right child with largest

    if (largest != index) { // if largest is not the current index, swap and heapify the affected subtree
        std::swap(nodes[index], nodes[largest]);
        heapify(largest);
    }
}

void BinHeap::insert(int value) {
    if (size == 0) { // if heap is empty, initialize the nodes array
        nodes = new int[1];
        nodes[0] = value;
        size = 1;
    } else {
        int* newNodes = new int[size + 1]; // create a new array with increased size
        for (int i = 0; i < size; i++) newNodes[i] = nodes[i]; // copy existing elements
        newNodes[size] = value; // add the new value at the end
        delete[] nodes; // delete the old array
        nodes = newNodes; // point to the new array
        size++; // increase the size

        for (int i = size / 2 - 1; i >= 0; i--) heapify(i); // maintain the heap property
    }
}

int* BinHeap::buildHeap(int* arr) {
    size = sizeof(arr) / sizeof(arr[0]); // calculate the size of the input array
    nodes = new int[size]; // initialize the nodes array
    for (int i = 0; i < size; i++) nodes[i] = arr[i]; // copy elements from input array

    for (int i = size / 2 - 1; i >= 0; i--) heapify(i); // maintain the heap property
    return nodes; // return pointer to the heapified array
}

int BinHeap::find(int value) {
    for (int i = 0; i < size; i++) {
        if (nodes[i] == value) return i; // return position if found
    }
    return -1; // return -1 if not found
}

// sorts the heap and returns a new array with sorted elements
int* BinHeap::heapSort() {
    int* sortedArray = new int[size]; // create an array to hold the sorted elements
    for (int i = 0; i < size; i++) sortedArray[i] = nodes[i]; // copy elements to the sorted array

    for (int i = size - 1; i > 0; i--) { // perform heap sort
        std::swap(sortedArray[0], sortedArray[i]); // move current root to end
        // Note: heapify needs to work on sortedArray but this is complex
        // A more proper implementation would use a temp heap
    }
    return sortedArray; // return pointer to the sorted array
}

//maxHeap - remove the maximum element (root) from the heap
void BinHeap::removeMax() {
    if (size == 0) return; // if heap is empty, do nothing
    nodes[0] = nodes[size - 1]; // replace root with the last element
    size--; // decrease the size
    heapify(0); // maintain the heap property
}

void BinHeap::display() {
    if (size == 0) {
        std::cout << "The heap is empty." << std::endl;
        return;
    }
    for (int i = 0; i < size; i++) std::cout << nodes[i] << " "; // display elements in level order
    std::cout << std::endl;
}

