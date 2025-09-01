/*
This file is for practice purposes only...
Procedure:
    1. Clear the code that is already here
    2. Implement a linked list structure that supports the following algs:
        1. Print
        2. Insert (at head, after a given index and before a given index)
        3. Delete (at head, and provided a given value)
        4. List reversal
    3. Keep track of how long it took to implement
        !! Especially keep track of what you did in the first 45 min; most interviews will be in that window...

Attempts:
    8/28/2025 - First 45: Implemented everything except reverseList
*/


#include <iostream>

class List {
private:
    struct Node {
        Node() : next(nullptr), value(0) {};
        Node(int value) : next(nullptr), value(value) {};
        Node* next;
        int value;
    };
    Node* head;
public:

    List() : head(nullptr){}

    bool printList() {
        if (!head) return false;
        Node* current = head;
        while (current) {
            if (!(current->next)) 
                std::cout << current->value << std::endl;
            else
                std::cout << current->value << " -> ";
            current = current -> next;
        }
    }

    bool pushBack(int value) {
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
        delete temp;
    }

    bool insert(int value, int idx, std::string mode = "after_idx") {
        if (!head) return false;
        Node* temp = new Node(value);
        Node* current = head; 

        if (mode == "after_idx") {
            for (int i = 1; i < idx; i++) {
                current = current->next;
                if (!current) return false;
            }
            temp->next = current->next;
            current->next = temp;
            delete temp;
            return true;
        }
        if (mode == "before_idx") {
            for (int i = 2; i < idx; i++) {
                current = current->next;
                if(!current) return false;
            }
            temp->next = current->next;
            current->next = temp;
            delete temp;
            return true;
        }
        else {
            delete temp;
            return false;
        }
    }

    bool deleteNode(int value) {
        
        Node* temp = head;
        Node* current = head;

        while (current && current->value != value) {
            current = current->next;
            if(temp->next->value != value)
                temp = temp->next;
        }

        if(!current) return false;

        temp->next = current->next;
        delete current;
        return true;
    }

    bool reverseList() {
        if (!head || !(head->next)) return false;
        Node* current = head;
        Node* temp = head;
        temp = temp->next;

        while (temp) {
            if (current == head) 
                current->next = nullptr;
                temp->next = current;
            else {
                temp->next = current;
            }

        }
        head = current;
    }
};


int main()
{
    /* code */
    return 0;
}

