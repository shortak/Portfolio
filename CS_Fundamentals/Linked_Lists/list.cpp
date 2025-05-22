#include <iostream>
#include <stdlib.h>

using namespace std;

class list_element
{
    public:
        list_element(int n = 0, list_element* ptr = 0): d(n), next(ptr){}
        int d;
        list_element* next;
};

class list
{
    public:
        list(): head(nullptr), current(nullptr){}
        void prepend(int n);
        int get_element(){return curret->d;}
        void advance(){current = current->next;}
        void print();
    private:
        list_element* head;
        list_element* current;
};

void list::prepend(int n)
{
    if(head == nullptr) current = head = new list_element(n, head);
    else head = new list_element(n, head);
}

void list::print()
{
    list_element* h = head;
    while (h != nullptr)
    {
        cout << h->d << ", " ;
    }
    cout << "###" << endl;
}