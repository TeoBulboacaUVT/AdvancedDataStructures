#include <iostream>
#include <fstream>
#include <string>
#include "MedianFunctions.h"

using namespace std;

int main() {
    MedianFinder mf;
    string command;
    int x;

    ifstream fin("test_input.txt");
    if (!fin.is_open()) {
        cerr << "Error: Could not open test_input.txt" << endl;
        return 1;
    }

    while (fin >> command) {
        if (command == "ADD") {
            fin >> x;
            mf.add(x);
        } else if (command == "REMOVE") {
            fin >> x;
            mf.remove(x);
        } else if (command == "MEDIAN") {
            cout << mf.getMedian() << endl;
        }
    }

    fin.close();
    return 0;
}
