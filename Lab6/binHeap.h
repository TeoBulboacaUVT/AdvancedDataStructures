#ifndef BINHEAP_H
#define BINHEAP_H

class BinHeap{
    private:
        int root;
        int size;
        int *nodes; // array to store pointers to nodes for easy access

    public:

        //initialize an empty binary heap
        BinHeap(){
            root = -1;
            size = 0;
            nodes = nullptr;
        }

        ~BinHeap();

        void heapify(int index); // function to maintain the heap property

        int* buildHeap(int* arr); // function to build a heap from an array, returns pointer to the heapifed array

        int find(int value); // function to find a value in the heap, returns position if found, -1 otherwise

        int* heapSort(); // function to perform heap sort and return a sorted array

        void insert(int value); // function to insert a new value into the heap

        void removeMax(); // function to remove the maximum element (root) from the heap

        void display(); // function to display the heap in level order

        bool isEmpty() {
            return size == 0;
        }

        int getSize() {
            return size;
        }

        int* getNodes() {
            return nodes;
        }

        int getRoot() {
            return root;
        }

        int getNode(int index) {
            if (index >= 0 && index < size) return nodes[index];
            return -1; // return -1 for invalid index
        }
};
#endif