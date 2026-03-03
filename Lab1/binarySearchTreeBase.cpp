#include <iostream>


class Tree{

    public:
    class node{
        public:
            int key;
            node* left;
            node* right;

            node(int value){
                key = value;
                left = nullptr;
                right = nullptr;
            }
    };
    
    private:
    node* root;
    
    public:    
        Tree(){
            root = nullptr;
        }

        void insert(int value){
            node *tmp = new node(value);
            if(root == nullptr){ //empty tree, insert as root
                root = tmp;
                return;
            }

            node *current = root;
            while(true){
                if(value < current->key){
                    if(current->left == nullptr){ //check if left child is empty, if so insert here
                        current->left = tmp;
                        return;
                    }
                    current = current->left; //else keep traversing
                }
                else{
                    if(current->right == nullptr){ //check if right child is empty, if so insert here
                        current->right = tmp;
                        return;
                    }
                    current = current->right; //else keep traversing
                }
            }

        }

        bool delete_node(int value){
            if(this->find_value(value) == false){
                std::cout << "Value not found, cannot delete: " << value << std::endl;
                return false;
            }

            node *current = root;
            node *parent = nullptr;
            while(current != nullptr && current->key != value){
                parent = current;
                if(value < current->key){
                    current = current->left;
                }else{
                    current = current->right;
                }
            }

            if(current == nullptr){
                std::cout << "Value not found, cannot delete: " << value << std::endl;
                return false;
            }

            // Case 1: Node has no children (leaf node)
            if(current->left == nullptr && current->right == nullptr){
                if(parent == nullptr){ //delete the root, empty the tree
                    root = nullptr;
                }else{
                    if(parent->left == current){
                        parent->left = nullptr;
                    }else{
                        parent->right = nullptr;
                    }
                }
                delete current;
                std::cout << "Value deleted: " << value << std::endl;
                return true;
            }

            // Case 2: Node has one child
            if(current->left == nullptr || current->right == nullptr){
                node *child = (current->left != nullptr) ? current->left : current->right; //get the non-null child

                if(parent == nullptr){
                    root = child;
                }else{
                    if(parent->left == current){ //jump over the current node and link parent to child
                        parent->left = child;
                    }else{
                        parent->right = child;
                    }
                }
                delete current;
                std::cout << "Value deleted: " << value << std::endl;
                return true;
            }

            // Case 3: Node has two children
            else {
                node *successor = current->right; //go one step right, then keep going left to find the successor
                node *successor_parent = current;

                while(successor->left != nullptr){ //keep going left until we find the successor
                    successor_parent = successor;
                    successor = successor->left;
                }

                current->key = successor->key; //overrite current node's value with successor's value

                if(successor_parent->left == successor){ //delete the successor node
                    successor_parent->left = successor->right; //link successor's parent to successor's right child (successor cannot have a left child)
                }
                else{
                    successor_parent->right = successor->right; //link successor's parent to successor's right
                }

                delete successor;
                std::cout << "Value deleted: " << value << std::endl;
                return true;
            }
        }


        bool find_value(int value){
            node *current = root;

            while(current != nullptr){
                if(value == current->key){
                    std::cout << "Value found: " << value << std::endl;
                    return true;
                }
                else if(value < current->key){
                    current = current->left;
                }else{
                    current = current->right;
                }
            }
        
            std::cout << "Value not found: " << value << std::endl;
            return false;
        }

        node *get_root(){
            return root;
        }

        node *maximum(){
            if(root == nullptr){
                std::cout << "Tree is empty, no maximum value." << std::endl;
                return nullptr;
            }

            node *current = root;
            while(current->right != nullptr){//keep traversing right until we find the maximum
                current = current->right;
            }
            std::cout << "Maximum value: " << current->key << std::endl;
            return current;
        }

        node *minimum(){
            if(root == nullptr){
                std::cout << "Tree is empty, no minimum value." << std::endl;
                return nullptr;
            }

            node *current = root;
            while(current->left != nullptr){//keep traversing left until we find the minimum
                current = current->left;
            }
            std::cout << "Minimum value: " << current->key << std::endl;
            return current;
        }
};

