#include "testFunctions.h"
#include <iostream>

int main(){
    std::cout << "Testing BinHeap:" << std::endl;
    testBinHeap();

    std::cout << "\nTesting Priority Queue:" << std::endl;
    testPriorityQueue();

    return 0;
}