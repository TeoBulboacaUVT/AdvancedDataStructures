#ifndef LEADERBOARD_FUNCTIONS_H
#define LEADERBOARD_FUNCTIONS_H

#include "PlayerRBTree.h"
#include <string>
#include <unordered_map>

using namespace std;

class Player {
private:
    string name;
    int score;

public:

    //constructor - default score 0, empty name
    Player(string n = "", int s = 0) : name(n), score(s) {}

    //getters and setters for encapsulation
    string getName() const { return name; }
    int getScore() const { return score; }
    void setScore(int s) { score = s; }
};

struct Leaderboard {
    PlayerRBTree tree;
    unordered_map<string, PlayerNode*> nameToNode;

    //add - adds a new player to the leaderboard
    void add(string name, int score) {
        if (nameToNode.find(name) != nameToNode.end()) {
            return;
        }
        PlayerNode* node = tree.insert(name, score);
        nameToNode[name] = node;
    }

    //update - updates the score of a player
    void update(string name, int delta) {
        auto it = nameToNode.find(name);
        if (it != nameToNode.end()) {
            PlayerNode* node = it->second;
            int newScore = node->score + delta;
            tree.remove(node, nameToNode);
            PlayerNode* newNode = tree.insert(name, newScore);
            nameToNode[name] = newNode;
        }
    }

    //remove - removes a player from the leaderboard
    void remove(string name) {
        auto it = nameToNode.find(name);
        if (it != nameToNode.end()) {
            tree.remove(it->second, nameToNode);
            nameToNode.erase(it);
        }
    }

    //top - prints the top k players
    void top(int k) {
        tree.printTop(k);
    }
};

#endif