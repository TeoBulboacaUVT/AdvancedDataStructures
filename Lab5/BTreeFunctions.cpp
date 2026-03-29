#include <iostream>
#include <queue>
#include "BTree.h"

#pragma region BTreeNode Functions

// constructor for BTreeNode
BTreeNode::BTreeNode(int _t, bool _leaf, BTreeNode *_parent) {
    t = _t; // minimum degree
    leaf = _leaf; // is leaf node
    parent = _parent; // parent pointer
    keys = new int[2 * t - 1]; // array of keys
    C = new BTreeNode*[2 * t]; // array of child pointers
    for (int i = 0; i < 2 * t; i++) C[i] = nullptr;
    n = 0; // number of keys
}

// destructor for BTreeNode
BTreeNode::~BTreeNode() {
    if (leaf == false) {
        for (int i = 0; i <= n; i++) {
            delete C[i];
        }
    }
    delete[] keys;
    delete[] C;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false) C[i]->traverse();
        std::cout << " " << keys[i];
    }
    if (leaf == false) C[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (i < n && keys[i] == k) return this;
    if (leaf == true) return nullptr;
    return C[i]->search(k);
}

// insert a key into a non-full node - no structural changes
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k) i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// split child - structural change - median goes up to the parent
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf, this);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (y->leaf == false) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
            if (z->C[j]) z->C[j]->parent = z;
        }
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n = n + 1;
}

// insert a key into the tree
void BTree::insert(int k) {
    if (root == nullptr) { //empty tree case
        root = new BTreeNode(t, true, nullptr);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) { //root is full case
            BTreeNode *s = new BTreeNode(t, false, nullptr);
            s->C[0] = root;
            root->parent = s;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else root->insertNonFull(k); //root is not full case
    }
}

// remove a key from the tree
void BTree::remove(int k) {
    if (!root) { //empty tree case      
        std::cout << "The tree is empty\n";
        return;
    }
    root->remove(k);
    if (root->n == 0) { //root is empty case
        BTreeNode *tmp = root;
        if (root->leaf) root = nullptr;
        else {
            root = root->C[0];
            root->parent = nullptr;
            tmp->leaf = true; // Prevent recursive deletion of children that now belong to the new root
        }
        delete tmp;
    }
}

// remove a key from a node
void BTreeNode::remove(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k) idx++;
    if (idx < n && keys[idx] == k) {
        if (leaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            std::cout << "The key " << k << " does not exist in the tree\n";
            return;
        }
        bool flag = (idx == n);
        if (C[idx]->n < t) fill(idx);
        if (flag && idx > n) C[idx - 1]->remove(k);
        else C[idx]->remove(k);
    }
}

// remove a key from a leaf node
void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++) keys[i - 1] = keys[i];
    n--;
}

// remove a key from a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (C[idx]->n >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

// get predecessor of a key
int BTreeNode::getPred(int idx) {
    BTreeNode *curr = C[idx];
    while (curr->leaf == false) curr = curr->C[curr->n];
    return curr->keys[curr->n - 1];
}

// get successor of a key
int BTreeNode::getSucc(int idx) {
    BTreeNode *curr = C[idx + 1];
    while (curr->leaf == false) curr = curr->C[0];
    return curr->keys[0];
}

// fill a node with keys from its siblings
void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t) borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t) borrowFromNext(idx);
    else {
        if (idx != n) merge(idx);
        else merge(idx - 1);
    }
}

// borrow a key from the previous sibling
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];
    for (int i = child->n - 1; i >= 0; i--) child->keys[i + 1] = child->keys[i];
    if (child->leaf == false) {
        for (int i = child->n; i >= 0; i--) child->C[i + 1] = child->C[i];
        child->C[0] = sibling->C[sibling->n];
        if (child->C[0]) child->C[0]->parent = child;
    }
    child->keys[0] = keys[idx - 1];
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// borrow a key from the next sibling
void BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];
    child->keys[child->n] = keys[idx];
    if (child->leaf == false) {
        child->C[child->n + 1] = sibling->C[0];
        if (child->C[child->n + 1]) child->C[child->n + 1]->parent = child;
    }
    keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->n; i++) sibling->keys[i - 1] = sibling->keys[i];
    if (sibling->leaf == false) {
        for (int i = 1; i <= sibling->n; i++) sibling->C[i - 1] = sibling->C[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

// merge two siblings
void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];
    child->keys[t - 1] = keys[idx];
    for (int i = 0; i < sibling->n; i++) child->keys[i + t] = sibling->keys[i];
    if (child->leaf == false) {
        for (int i = 0; i <= sibling->n; i++) {
            child->C[i + t] = sibling->C[i];
            if (child->C[i + t]) child->C[i + t]->parent = child;
        }
    }
    for (int i = idx + 1; i < n; i++) keys[i - 1] = keys[i];
    for (int i = idx + 2; i <= n; i++) C[i - 1] = C[i];
    child->n += sibling->n + 1;
    n -= 1;
    
    sibling->leaf = true; // Prevent recursive deletion of sibling's children as they have been moved to child
    delete sibling;
}

// destructor for BTree
BTree::~BTree() {
    if (root != nullptr) delete root;
}

void BTree::display() {
    if (root == nullptr) {
        std::cout << "The tree is empty." << std::endl;
        return;
    }

    std::queue<std::pair<BTreeNode*, int>> q;
    q.push({root, 0});
    int currentLevel = -1;

    while (!q.empty()) {
        BTreeNode* node = q.front().first;
        int level = q.front().second;
        q.pop();

        if (level != currentLevel) {
            std::cout << "\nLevel " << level << ": ";
            currentLevel = level;
        }

        std::cout << *node << " ";

        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++) {
                if (node->C[i]) q.push({node->C[i], level + 1});
            }
        }
    }
    std::cout << std::endl;
}

void BTreeNode::display(int level) {
    // This could be used for a recursive indented display if preferred
    // But BTree::display already implements level-order.
}

std::ostream& operator<<(std::ostream &os, const BTreeNode &node) {
    os << "[";
    for (int i = 0; i < node.n; i++) {
        os << node.keys[i] << (i < node.n - 1 ? "," : "");
    }
    os << "]";
    
    if (node.parent) {
        os << "(P: ";
        for (int i = 0; i < node.parent->n; i++) {
            os << node.parent->keys[i] << (i < node.parent->n - 1 ? "," : "");
        }
        os << ")";
    } else {
        os << "(ROOT)";
    }
    
    os << "{" << (node.leaf ? "Leaf" : "Non-Leaf") << "}";
    return os;
}

#pragma endregion