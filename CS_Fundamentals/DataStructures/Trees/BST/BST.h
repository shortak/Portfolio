#ifndef BTREE_H
#define BTREE_H

#include <vector>

class BST {
private:
    struct Node {
        int data;
        Node* right;
        Node* left;
        Node(int data) {
            this->data = data;
            Node* right = nullptr;
            Node* left = nullptr;
        }
    };
    Node* root;
public:
    BST() : root(nullptr){}; 
    void deleteTree(Node* root);
    ~BST();
    bool insertNode(int value);
    void printPreorder(Node* root);
    void printInorder(Node* root);
    void printPostorder(Node* root);
    bool deleteNode(int value);
    int findHeight();
    std::vector<std::vector<int>> levelOrder();
};


#endif