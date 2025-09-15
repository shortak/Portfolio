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

    9/4/2025 - First 45: Implemented everything (attempted) 
*/


#include <iostream>
#include <stdlib.h>

class List {
    private:
        struct Node {
            int data;
            Node* next;
            Node(int value) : data(value), next(nullptr) {}
        };

        Node* head;
    public:
        List() : head(nullptr) {}
        ~List() {
            
        }

        void print(){
            Node* current = head;
            if (!current) return;
            while (current) {
                if (!(current->next)) 
                    std::cout << current->data << std::endl;
                else {
                    std::cout << current->data << " -> ";
                }
                current = current->next;
            }
        }

        void insertNode(int data) {
            Node* temp = new Node(data);
            temp->next = head;
            head = temp;
        }

        bool insertNodeIdx(int idx, int data, std::string mode = "after"){
            Node* current = head;
            Node* temp = new Node(data);

            if (mode == "after") {
                if (!(current->next)) {
                    current->next = temp;
                    return true;
                }
                for (int i = 1; i < idx; i++) {
                    current = current->next;
                }

                temp->next = current->next;
                current->next = temp;
                
                return true;

            } else if (mode == "before") {
                if (!(current->next)) {
                    temp->next = current;
                    head = temp;
                    return true;
                }

                Node* prev = current;

                for (int i = 1; i < idx; i++) {
                    prev = current;
                    current = current->next;
                }

                temp->next = prev->next;
                prev->next = temp;

                return true;

            }
            delete temp;
            return false;
        }
        bool deleteNode(int data) {
            Node* prev = head;
            Node* current = head;
            while (current) {
                prev = current;
                current = current->next;
                if (current->data == data) {
                    prev->next = current->next;
                    delete current;
                    return true;
                }
            }
            return false;
        }
        void reverse() {
            if (!head) return;
            Node* current = head;
            Node* prev = nullptr;
            Node* next = head;
            while (current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }
};


int main()
{
    // test insert at head
    List list{};

    for (int i = 4; i > 0; i--) {
        list.insertNode(i);
    }
    list.print();

    // test insert before and after given idx
    list.insertNodeIdx(1, 10, "after");
    list.insertNodeIdx(4, 20, "before");
    list.print(); 

    // test delete
    list.deleteNode(20);
    list.deleteNode(10);
    list.print();

    // test reverse
    list.reverse();
    list.print();


    return 0;
}

