#include <fstream>
#include <iostream>
#include <string>
#include "LeaderboardFunctions.h"

using namespace std;

int main() {
    Leaderboard lb;
    string command;

    ifstream fin("test_input.txt");

    if(!fin.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (fin >> command) {
        if (command == "ADD") {
            string name;
            int score;
            fin >> name >> score;
            lb.add(name, score);
        } else if (command == "UPDATE") {
            string name;
            int delta;
            fin >> name >> delta;
            lb.update(name, delta);
        } else if (command == "REMOVE") {
            string name;
            fin >> name;
            lb.remove(name);
        } else if (command == "TOP") {
            int k;
            fin >> k;
            lb.top(k);
        }
    }   

    return 0;
}
