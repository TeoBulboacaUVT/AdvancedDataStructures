#include "BTree.h"
#include <iostream>

int main() {
    BTree tree(3);
    int nodes[] = {1, 3, 4, 5, 10, 11, 14, 15, 7, 13, 16, 23, 18, 19, 20, 21, 22, 24, 26};
    for (int i = 0; i < 19; i++) {
        tree.insert(nodes[i]);
    }
    std::cout <<"Initial tree: \n";
    tree.display();
    std::cout << "\n";
    tree.insert(2);
    std::cout <<"Tree after inserting 2: \n";
    tree.display();
    std::cout << "\n";
    tree.insert(17);
    std::cout <<"Tree after inserting 17: \n";
    tree.display();
    std::cout << "\n";
    tree.insert(12);
    std::cout <<"Tree after inserting 12: \n";
    tree.display();
    std::cout << "\n";
    tree.insert(6);
    std::cout <<"Tree after inserting 6: \n";
    tree.display();
    std::cout << "\n";
    tree.remove(6);
    std::cout <<"Tree after removing 6: \n";
    tree.display();
    std::cout << "\n";
    tree.remove(13);
    std::cout <<"Tree after removing 13: \n";
    tree.display();
    std::cout << "\n";
    tree.remove(7);
    std::cout <<"Tree after removing 7: \n";
    tree.display();
    std::cout << "\n";
    tree.remove(4);
    std::cout <<"Tree after removing 4: \n";
    tree.display();
    std::cout << "\n";
    tree.remove(2);
    std::cout <<"Tree after removing 2: \n";
    tree.display();
    std::cout << "\n";

    std::cout << "Final tree: \n";
    tree.display();
    std::cout << "\n";  

    BTreeNode* res = tree.search(15);
    if (res) std::cout << "Search 15: " << *res << "\n";
    
    res = tree.search(21);
    if (res) std::cout << "Search 21: " << *res << "\n";
    
    res = tree.search(100);
    if (!res) std::cout << "Search 100: Not Found\n";

    std::cout << "\n";
    return 0;
}