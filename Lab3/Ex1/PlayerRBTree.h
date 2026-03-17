#ifndef PLAYER_RBTREE_H
#define PLAYER_RBTREE_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

struct PlayerNode {
    string name;
    int score;
    PlayerNode *p, *left, *right;
    enum Color { RED, BLACK } col;

    PlayerNode(string n = "", int s = 0) : name(n), score(s), p(nullptr), left(nullptr), right(nullptr), col(BLACK) {}
};

class PlayerRBTree {
private:
    PlayerNode* nil;
    PlayerNode* root;

    void leftRotate(PlayerNode* x) {
        PlayerNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->p = x;
        y->p = x->p;
        if (x->p == nil) root = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->left = x;
        x->p = y;
    }

    void rightRotate(PlayerNode* y) {
        PlayerNode* x = y->left;
        y->left = x->right;
        if (x->right != nil) x->right->p = y;
        x->p = y->p;
        if (y->p == nil) root = x;
        else if (y == y->p->left) y->p->left = x;
        else y->p->right = x;
        x->right = y;
        y->p = x;
    }

    void insertFixup(PlayerNode* z) {
        while (z->p->col == PlayerNode::RED) {
            if (z->p == z->p->p->left) {
                PlayerNode* y = z->p->p->right;
                if (y->col == PlayerNode::RED) {
                    z->p->col = PlayerNode::BLACK;
                    y->col = PlayerNode::BLACK;
                    z->p->p->col = PlayerNode::RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->col = PlayerNode::BLACK;
                    z->p->p->col = PlayerNode::RED;
                    rightRotate(z->p->p);
                }
            } else {
                PlayerNode* y = z->p->p->left;
                if (y->col == PlayerNode::RED) {
                    z->p->col = PlayerNode::BLACK;
                    y->col = PlayerNode::BLACK;
                    z->p->p->col = PlayerNode::RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->col = PlayerNode::BLACK;
                    z->p->p->col = PlayerNode::RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->col = PlayerNode::BLACK;
    }

    void deleteFixup(PlayerNode* x) {
        while (x != root && x->col == PlayerNode::BLACK) {
            if (x == x->p->left) {
                PlayerNode* w = x->p->right;
                if (w->col == PlayerNode::RED) {
                    w->col = PlayerNode::BLACK;
                    x->p->col = PlayerNode::RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->col == PlayerNode::BLACK && w->right->col == PlayerNode::BLACK) {
                    w->col = PlayerNode::RED;
                    x = x->p;
                } else {
                    if (w->right->col == PlayerNode::BLACK) {
                        w->left->col = PlayerNode::BLACK;
                        w->col = PlayerNode::RED;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->col = x->p->col;
                    x->p->col = PlayerNode::BLACK;
                    w->right->col = PlayerNode::BLACK;
                    leftRotate(x->p);
                    x = root;
                }
            } else {
                PlayerNode* w = x->p->left;
                if (w->col == PlayerNode::RED) {
                    w->col = PlayerNode::BLACK;
                    x->p->col = PlayerNode::RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->col == PlayerNode::BLACK && w->left->col == PlayerNode::BLACK) {
                    w->col = PlayerNode::RED;
                    x = x->p;
                } else {
                    if (w->left->col == PlayerNode::BLACK) {
                        w->right->col = PlayerNode::BLACK;
                        w->col = PlayerNode::RED;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->col = x->p->col;
                    x->p->col = PlayerNode::BLACK;
                    w->left->col = PlayerNode::BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->col = PlayerNode::BLACK;
    }

    //isLessThan - compares two players based on their scores and names - if the scores are equal, the player with the lexicographically smaller name is considered smaller
    bool isLessThan(const string& n1, int s1, const string& n2, int s2) {
        if (s1 != s2) return s1 < s2;
        return n1 > n2;
    }

public:
    //constructor - creates a new RB tree with a nil node
    PlayerRBTree() {
        nil = new PlayerNode();
        nil->col = PlayerNode::BLACK;
        root = nil;
    }

    //destructor - deletes the tree
    ~PlayerRBTree() {
        deleteTree(root);
        delete nil;
    }

    //deleteTree - deletes the tree
    void deleteTree(PlayerNode* node) {
        if (node != nil && node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    //insert - inserts a new player in the tree
    PlayerNode* insert(string name, int score) {
        PlayerNode* z = new PlayerNode(name, score);
        PlayerNode* y = nil;
        PlayerNode* x = root;
        while (x != nil) {
            y = x;
            if (isLessThan(z->name, z->score, x->name, x->score)) x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (y == nil) root = z;
        else if (isLessThan(z->name, z->score, y->name, y->score)) y->left = z;
        else y->right = z;

        z->left = z->right = nil;
        z->col = PlayerNode::RED;
        insertFixup(z);
        return z;
    }

    //remove - removes a player from the tree
    void remove(PlayerNode* z, unordered_map<string, PlayerNode*>& map) {
        PlayerNode* y = (z->left == nil || z->right == nil) ? z : successor(z);
        PlayerNode* x = (y->left != nil) ? y->left : y->right;

        x->p = y->p;
        if (y->p == nil) root = x;
        else if (y == y->p->left) y->p->left = x;
        else y->p->right = x;

        bool yWasBlack = (y->col == PlayerNode::BLACK);

        if (y != z) {
            // Update map: player at y is moved to z
            map[y->name] = z;
            z->name = y->name;
            z->score = y->score;
        }

        if (yWasBlack) deleteFixup(x);
        delete y;
    }

    //successor - finds the successor of a node
    PlayerNode* successor(PlayerNode* x) {
        if (x->right != nil) return minimum(x->right);
        PlayerNode* y = x->p;
        while (y != nil && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }

    //predecessor - finds the predecessor of a node
    PlayerNode* predecessor(PlayerNode* x) {
        if (x->left != nil) return maximum(x->left);
        PlayerNode* y = x->p;
        while (y != nil && x == y->left) {
            x = y;
            y = y->p;
        }
        return y;
    }

    //minimum - finds the minimum element in the tree
    PlayerNode* minimum(PlayerNode* x) {
        while (x->left != nil) x = x->left;
        return x;
    }

    //maximum - finds the maximum element in the tree
    PlayerNode* maximum(PlayerNode* x) {
        if (x == nil) return nil;
        while (x->right != nil) x = x->right;
        return x;
    }

    //printTop - prints the top k players
    void printTop(int k) {
        PlayerNode* curr = maximum(root);
        for (int i = 0; i < k && curr != nil; ++i) {
            cout << curr->name << " " << curr->score << endl;
            curr = predecessor(curr);
        }
    }

    PlayerNode* getNil() { return nil; }
    PlayerNode* getRoot() { return root; }
};

#endif
