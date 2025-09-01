#include <iostream>
#include <string>
#include "LinkedLists.h"

/*
THINGS TO NOTE:

    Anytime you work with the heap (using new operator), always remember who owns and has access to that pointer:

    using ~SNode:
        - You originally just did "delete head" this only deletes one node (the head node) but you need to walk through and delete each node in the list
    using delete Node:
        - You originally just did current->next = current->next->next... this DOES NOT OVERWRITE data, just transfers pointer ownership... the original current->next still exists, but cannot be accessed, causing a mem leak
        - Make sure you store current-next into a temp variable so that you have access to the orinial mem space via temp, then delete the temp node
    using insertNode:
        - You have different modes defined... always thing about what happens when a user uses this function but for some reason, they use a mode that is not defined in the function... 
          now you have an issue where you allocated a new node, but have done nothing with it, resulting in a mem leak... always delete the new Node at the end by default if we don't hit a return condition
    
    As far as implementing the actual algorithm:
    
    Common patterns:
        - linking nodes: doing something like current->next = node will actually link a node to the list
        - replacing nodes: in a situation where you might want to insert a node or delete a node...
            1. Work from the new node... link newNode->next to the next node FIRST, then link newNode to the current node
            OR
            2. Use a temp variable to maintain a pointer access to a node (e.g. the delete function)
*/



SList::~SList() {
    SNode* current = head;
    while (current) {
        SNode* next = current -> next;
        delete current;
        current = next;
    }
    head = nullptr;
}

bool SList::placeFront(int value) {
    SNode* newNode = new SNode(value);
    newNode -> next = head;
    head = newNode;
    return true;
}

bool SList::search(int value) {
    if (!head) return false;

    SNode* current = head;
    while (current) {
        if (current -> value == value) {
            std::cout << "Found value: " << std::endl;
            return true;
        }
        current = current -> next;
    }
    return false;
}

bool SList::deleteNode(int value) {
    SNode* current = head;
    SNode* temp;
    while(current -> next != nullptr) {
        if (current -> next -> value == value && current -> next -> next) {
            temp = current -> next; //Give ownership of pointer to temp to still retain access
            current -> next = current -> next -> next;
            delete temp; //Delete the node to avoid mem leak
            return true;
        }
        current = current -> next;
    }
    return false;
}

void SList::printList() {
    SNode* current = head;
    while (current != nullptr) {
        if(current -> next != nullptr) std::cout << current -> value << ", ";
        else std::cout << current-> value << std::endl;
        current = current -> next;
    }
}

bool SList::placeBack(int value) {
    SNode* current = head;
    SNode* newNode = new SNode(value);
    while (current != nullptr) {
        if(current -> next == nullptr){
            current -> next = newNode;
            return true;
        }
        current = current -> next;
    }
    return false;
}

bool SList::insertNode(size_t idx, int value, std::string mode) {
    if (!head) {return false;}
    
    SNode* current = head;
    SNode* newNode = new SNode(value);
    if (mode == "after_idx") {
        for (size_t i = 1; i < idx; i++) {
            if (!current) {return false;}

            current = current -> next;
        }
        newNode -> next = current -> next; //assign the newNode -> next first to preserve the current -> next node
        current -> next = newNode;
        return true;
    }
    if (mode == "before_idx") {
        for (size_t i = 2; i < idx; i++) {
            if (!current) {return false;}

            current = current -> next;
        }
        newNode -> next = current -> next;
        current -> next = newNode;
        return true;
    }

    delete newNode;
    return false;
}

void SList::findKthFromEnd(int K) {
    SNode* main_ptr = head;
    SNode* ref_ptr = head;

    if (!head || K < 0) {
        if(!head) std::cout <<"List DNE" << std::endl;
        else std::cout << "Please enter positive K";
    }

    for (size_t i = 0; i <= K; i++) {
        if (!ref_ptr) {
            std::cout << "List is too short" << std::endl;
            return;
        }
        ref_ptr = ref_ptr -> next;
    }

    while (ref_ptr) {
        ref_ptr = ref_ptr -> next;
        main_ptr = main_ptr -> next;
    }

    std::cout << main_ptr -> value << std::endl;
}

bool SList::reverseList() {
    if (!head) return false;
    SNode* current = head;
    SNode* prev = nullptr;
    SNode* next;
    while (current) {
        next = current -> next; //Keep an alias of next pointer
        current -> next = prev; //Swap the prev and next pointers
        prev = current; //Move pointer from prev to current to set up next swap
        current = next; //increment current
    }
    head = prev;
    return true;
}

