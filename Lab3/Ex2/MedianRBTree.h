#ifndef MEDIAN_RBTREE_H
#define MEDIAN_RBTREE_H

#include <iostream>

struct Node {
    int value;
    int size;
    Node *p, *left, *right;
    enum Color { RED, BLACK } col;



    //constructor - default value 0, size 1, black color, no parent or children
    Node(int v = 0) : value(v), size(1), p(nullptr), left(nullptr), right(nullptr), col(BLACK) {}
};

class MedianRBTree {
private:
    Node* nil;
    Node* root;

    void updateSize(Node* x) {
        //update size of node x
        if (x != nil) {
            x->size = x->left->size + x->right->size + 1;
        }
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->p = x;
        y->p = x->p;
        if (x->p == nil) root = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->left = x;
        x->p = y;
        
        updateSize(x);
        updateSize(y);
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nil) x->right->p = y;
        x->p = y->p;
        if (y->p == nil) root = x;
        else if (y == y->p->left) y->p->left = x;
        else y->p->right = x;
        x->right = y;
        y->p = x;

        updateSize(y);
        updateSize(x);
    }

    void insertFixup(Node* z) {
        while (z->p->col == Node::RED) {
            if (z->p == z->p->p->left) {
                Node* y = z->p->p->right;
                if (y->col == Node::RED) {
                    z->p->col = Node::BLACK;
                    y->col = Node::BLACK;
                    z->p->p->col = Node::RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->col = Node::BLACK;
                    z->p->p->col = Node::RED;
                    rightRotate(z->p->p);
                }
            } else {
                Node* y = z->p->p->left;
                if (y->col == Node::RED) {
                    z->p->col = Node::BLACK;
                    y->col = Node::BLACK;
                    z->p->p->col = Node::RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->col = Node::BLACK;
                    z->p->p->col = Node::RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->col = Node::BLACK;
    }

    void deleteFixup(Node* x) {
        while (x != root && x->col == Node::BLACK) {
            if (x == x->p->left) {
                Node* w = x->p->right;
                if (w->col == Node::RED) {
                    w->col = Node::BLACK;
                    x->p->col = Node::RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->col == Node::BLACK && w->right->col == Node::BLACK) {
                    w->col = Node::RED;
                    x = x->p;
                } else {
                    if (w->right->col == Node::BLACK) {
                        w->left->col = Node::BLACK;
                        w->col = Node::RED;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->col = x->p->col;
                    x->p->col = Node::BLACK;
                    w->right->col = Node::BLACK;
                    leftRotate(x->p);
                    x = root;
                }
            } else {
                Node* w = x->p->left;
                if (w->col == Node::RED) {
                    w->col = Node::BLACK;
                    x->p->col = Node::RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->col == Node::BLACK && w->left->col == Node::BLACK) {
                    w->col = Node::RED;
                    x = x->p;
                } else {
                    if (w->left->col == Node::BLACK) {
                        w->right->col = Node::BLACK;
                        w->col = Node::RED;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->col = x->p->col;
                    x->p->col = Node::BLACK;
                    w->left->col = Node::BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->col = Node::BLACK;
    }

    void deleteTree(Node* node) {
        if (node != nil && node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    //constructor - creates a new RB tree with a nil node
    MedianRBTree() {
        nil = new Node();
        nil->col = Node::BLACK;
        nil->size = 0;
        nil->left = nil->right = nil->p = nil;
        root = nil;
    }

    //destructor - deletes the tree
    ~MedianRBTree() {
        deleteTree(root);
        delete nil;
    }

    //insert - inserts a new node in the tree
    void insert(int v) {
        Node* z = new Node(v);
        z->left = z->right = z->p = nil;
        Node* y = nil;
        Node* x = root;
        while (x != nil) {
            y = x;
            if (z->value < x->value) x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (y == nil) root = z;
        else if (z->value < y->value) y->left = z;
        else y->right = z;

        z->col = Node::RED;
        
        // Update sizes from z up to root
        Node* temp = z;
        while (temp != nil) {
            updateSize(temp);
            temp = temp->p;
        }

        insertFixup(z);
    }

    //search - searches for a node with value v
    Node* search(int v) {
        Node* x = root;
        while (x != nil && x->value != v) {
            if (v < x->value) x = x->left;
            else x = x->right;
        }
        return x;
    }

    //remove - removes a node with value v
    void remove(int v) {
        Node* z = search(v);
        if (z == nil) return;

        Node* y = (z->left == nil || z->right == nil) ? z : successor(z);
        Node* x = (y->left != nil) ? y->left : y->right;
        Node* xP = y->p;

        if (x != nil) x->p = y->p;
        
        if (y->p == nil) root = x;
        else if (y == y->p->left) y->p->left = x;
        else y->p->right = x;

        bool yWasBlack = (y->col == Node::BLACK);

        if (y != z) {
            z->value = y->value;
        }

        // Update sizes from xP up to root
        Node* temp = xP;
        while (temp != nil) {
            updateSize(temp);
            temp = temp->p;
        }

        if (yWasBlack) deleteFixup(x);
        delete y;
    }

    Node* successor(Node* x) {
        if (x->right != nil) return minimum(x->right);
        Node* y = x->p;
        while (y != nil && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }

    Node* minimum(Node* x) {
        while (x->left != nil) x = x->left;
        return x;
    }

    //select - selects the k-th smallest element in the tree
    int select(int k) {
        Node* x = root;
        while (x != nil) {
            int r = x->left->size + 1;
            if (k == r) return x->value;
            if (k < r) x = x->left;
            else {
                k -= r;
                x = x->right;
            }
        }
        return -1; // Should not happen
    }

    //totalSize - returns the total number of elements in the tree
    int totalSize() {
        return root->size;
    }
};

#endif
