#include <iostream>
#include "BTree.h"

template <typename T, int ORDER>
BTree<T, ORDER>::~BTree() {

}

template <typename T, int ORDER>
T BTree<T, ORDER>::traverse(){
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        cout << " " << root->keys[i];
    }
    if (!root->leaf) 
        traverse(root->children[i]);
}

template <typename T, int ORDER>
void BTree<T, ORDER>::splitChild(int i){
    BTreeNode<T, ORDER>* y = root->children[i];
    BTreeNode<T, ORDER>* z = new BTreeNode<T, ORDER>(y->leaf);
    z->n = ORDER/2 - 1;

    for (int j = 0; j < ORDER/2 - 1; j++)
        z->keys[j] = y->keys[j + ORDER / 2];
    if (!y->leaf) {
        for (int j = 0; j < ORDER/2; j++)
            z->children[j] = y->children[j + ORDER/2];
    }

    y->n = ORDER/2 - 1;

    for (int j = root->children; j >= i + 1; j--)
        root->children[j + 1] = x->children[j];

    root->children[i + 1] = z;

    for (int j = root->n - 1; j >= i; j--)
        root->keys[h + 1] = root->keys[j];
    
        root->keys[i] = y->keys[ORDER/2 -1];
        root->n = root->n + 1
    
}

template <typename T, int ORDER>
void BTree<T, ORDER>::insertNonFull(T key) {
    int i = root->n - 1;
    if (root->leaf) {
        while (i >=0 && k < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }

        root->keys[i + 1] = k;
        root->n = root->n + 1;
    } else {
        while (i >= 0 && k < root->keys[i])
            i--;
        
        i++;
        if (root->children[i]->n == ORDER-1) {
            splitChild(i);

            if (key > root->keys[i])
                i++;
        }
        insertNonFull(root->children[i], k);
    }
}

template <typename T, int ORDER>
T BTree<T, ORDER>::search(T key){
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;

    if (i < root->n && k == root->keys[i])
        return x;

    if (x->leaf)
        return nullptr;

    return search(x->children[i], k);
}

template <typename T, int ORDER>
void BTree<T, ORDER>::merge(BTreeNode* node, int idx) {
    BTreeNode<T, ORDER>* child = node->children[idx];
    BTreeNode<T, ORDER>* sibling = node->children[idx + 1];

    child->keys[ORDER/2 + 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + ORDER/2] = sibling->keys[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + ORDER/2] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->; ++i)
        node->keys[i - 1] = node->keys[i];
    for (int i = idx +2; i <= node->n; ++i)
        node->children[i - 1] = node->children[i];
    
        child->n += sibling->n + 1;
        node->n--;

        delete sibling;
}


template <typename T, int ORDER>
void BTree<T, ORDER>::deleteNode(BTreeNode* node, int idx) {
    T k = node->keys[idx];

    if (node->children[idx]->n >= ORDER/2) {
        T pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        remove()
    }
}