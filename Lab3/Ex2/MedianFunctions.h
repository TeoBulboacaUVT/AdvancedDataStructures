#ifndef MEDIAN_FUNCTIONS_H
#define MEDIAN_FUNCTIONS_H

#include "MedianRBTree.h"

class MedianFinder {
private:
    MedianRBTree tree;

public:
    void add(int x) {
        tree.insert(x);
    }

    void remove(int x) {
        tree.remove(x);
    }

    int getMedian() {
        int n = tree.totalSize();
        if (n == 0) return 0;
        int k = (n + 1) / 2; // Lower median
        return tree.select(k);
    }
};

#endif
