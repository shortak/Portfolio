#include <iostream>
#include <stdlib.h>

using namespace std;

class list_element
{
    public:
        list_element(int n = 0, list_element* ptr = nullptr): d(n), next(ptr){}
        int d;
        list_element* next;
};

class list
{
    public:
        list(): head(nullptr), current(nullptr){}
        void prepend(int n);
        int get_element(){return current->d;}
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
        h = h->next;
    }
    cout << "###" << endl;
}

int main()
{
    list a, b;
    a.prepend(9); a.prepend(8);
    cout << "list a" << endl;
    a.print();

    for(int i = 0; i < 40; ++i) b.prepend(i*i);
    cout << "list b" << endl;
    b.print();

    return 0;
}