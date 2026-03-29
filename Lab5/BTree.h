#include <iostream>

class BTreeNode {
    int *keys; // array of keys
    int t; // minimum degree    
    BTreeNode *parent; // parent pointer
    BTreeNode **C; // child pointers
    int n; // number of keys
    bool leaf; // is leaf node

    public:
    BTreeNode(int _t, bool _leaf, BTreeNode *_parent = nullptr);

    ~BTreeNode();

    void traverse();

    void display(int level);

    BTreeNode* search(int k);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    void remove(int k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int getPred(int idx);

    int getSucc(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

    void borrowFromNext(int idx);

    void merge(int idx);

    friend class BTree;
    friend std::ostream& operator<<(std::ostream &os, const BTreeNode &node);
};

class BTree {
    BTreeNode *root;
    int t;

    public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    ~BTree();

    // traverse the tree
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    // display the tree level by level
    void display();

    // search for a key
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // insert a key
    void insert(int k);

    // remove a key
    void remove(int k);
};