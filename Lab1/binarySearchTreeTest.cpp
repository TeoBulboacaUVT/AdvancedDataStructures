#include "binarySearchTreeBase.cpp"
#include <iostream>

int main(){
    Tree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    std::cout << "Tree after insertions:" << std::endl;
    std::cout <<"    10" << std::endl;
    std::cout <<"   /  \\" << std::endl;
    std::cout <<"  5    15" << std::endl;
    std::cout <<" / \\   / \\" << std::endl;
    std::cout <<"3   7 12  18" << std::endl;

    tree.find_value(7); // should find
    tree.find_value(4); // should not find

    tree.maximum(); // should be 18
    tree.minimum(); // should be 3

    tree.delete_node(5); // delete node with one child
    tree.delete_node(10); // delete node with two children
    tree.delete_node(20); // try to delete non-existent value
}