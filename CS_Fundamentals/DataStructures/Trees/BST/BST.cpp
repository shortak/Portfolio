#include <iostream>
#include "BST.h"
#include <vector>
#include <queue>

/*
THINGS TO NOTE:
    You have 2 types of traversal:
        BFS:
            - Level order
        DFS:
            - Preorder
            - Inorder
            - Postorder
    Different algorithms will be based on one of these traversal methods

    Traversal often requires you to keep track of the parent node; the overal process of traversing is similar to a linked list, but now you have to reassign the parent node upon each loop

    Deleting a node consists of...
    Single child case:
        1. Finding the node to delete
        2. Finding the root of the subtree (AKA its child)
        3. Linking the parent (prev) to the root (some placeholder) 
        4. Deleting the current node
    Both children case:
        1. Finding the node to delete
        2. Finding its inorder successor
        3. Swapping delete node data with inorder successor
        4. Delete the temp variable 
        !!! YOU DELETE THE TEMP NODE HERE, NOT THE CURRENT NODE LIKE IN THE OTHER CASES
*/

void BST::deleteTree(Node* root) {
    if (!root) return;

    deleteTree(root -> left);
    deleteTree(root -> right);

    std::cout << "Deleting node: " << root -> data << std::endl;
    delete root;
}

BST::~BST(){
    deleteTree(root);
}

bool BST::insertNode(int value) {
        if (!root) {
            root = new Node(value);
            return true;
        }
        
        Node* temp = new Node(value);
        Node* parent = nullptr;
        Node* current = root;
        while (current) {
            parent = current;
            if (current->data > value) {
                current = current -> left;
            } else if (current -> data < value) {
                current = current -> right;
            } else return false;
        }

        if (parent -> data > value)
            parent -> left = temp;
        else 
            parent -> right = temp;

        return true;
    }

void BST::printPreorder(Node* root) {
    if (!root) return;
    Node* current = root;
    std::cout << current -> data << " ";
    printPreorder(current -> left);
    printPreorder(current -> right);
}

void BST::printInorder(Node* root) {
    if (!root) return;
    Node* current = root;
    printInorder(current -> left);
    std::cout << current -> data << " ";
    printInorder(current -> right);
}

void BST::printPostorder(Node* root) {
    if (!root) return;
    Node* current = root;
    printInorder(current -> left);
    printInorder(current -> right);
    std::cout << current -> data << " ";
}

std::vector<std::vector<int>> BST::levelOrder() {
    if (!root) return {};

    std::queue<Node*> q;
    std::vector<std::vector<int>> res;

    q.push(root);
    int currLevel = 0;

    while (!q.empty()) {
        int len = q.size();
        res.push_back({});

        for (int i = 0; i < len; i++) {
            Node* node = q.front();
            q.pop();

            res[currLevel].push_back(node -> data);

            if (node -> left) q.push(node -> left);
            if (node -> right) q.push(node -> right);
        }
        currLevel++;
    }

    return res;
}

bool BST::deleteNode(int value) {
    Node* current = root;
    Node* prev;

    //Move current to the node to delete; keep track of parent node
    while (current && current -> data != value) {

        prev = current;

        if (value < current -> data)
            current = current -> left;
        else 
            current = current -> right;
    }

    if(!current) return false; //Node to delete doesn't exist

    //Single child case
    if (!(current -> left) || !(current -> right)) {
        Node* newCurrent; //Place holder for subtree

        // Find the root of the subtree to relink
        if (!(current->left)) 
            newCurrent = current -> right;
        else
            newCurrent = current -> left;

        if (!prev) 
            root = newCurrent;
        
        //Perform delete by linking prev to newCurrent and deleting the current node
        if (current == prev -> left)
            prev -> left = newCurrent;
        else
            prev -> right = newCurrent;
        
        delete current;    
        //NOTE: this also works for cases where the delete node is part of a long chain of single children since you are linking newCurrent (aka the root of the subtree) to the parent of the delete node
    }
    else { // Both children case
        Node* p = nullptr;
        Node* temp = current -> right;
        while (temp -> left) { //Find inorder successor
            p = temp; //Keep track of parent of inorder successor
            temp = temp -> left; //Find actual inorder successor
        }
        if (p) // check if the parent of inorder succ is curr (where p = nullptr)
            p -> left = temp -> right;
        else
            current -> right = temp -> right;

        current -> data = temp -> data;

        /*
        NOTE: In order to find the node to swap the delete node with such that the properties of a binary search tree is maintained, you need to find the inorder successor
        */

        delete temp;
    }
}

int BST::findHeight() {
    if (!root) return 0;

    std::queue<Node*> q;
    q.push(root);
    int depth = 0;

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();
            if (current -> left) 
                q.push(current -> left);
            if (current -> right);
                q.push(current -> right);
        }
        depth++;
    }
    return depth - 1;
}