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
private:
    list_element* head;
    list_element* current;
public:
    list() : head(nullptr), current(nullptr){}
    list(const int* arr, int n);
    list(const list& lst)
    {
        if(lst.head == nullptr){head = nullptr; current = nullptr;}
        else
        {
            current = lst.head;
            list_element* h = new list_element();
            list_element* prev;
            head = h;
            h->d = lst.head->d;
            prev = h;
            for(current = lst.head; current !=  nullptr;)
            {
                h = new list_element();
                h->d = current->d;
                prev->next = h;
                current = current->next;
                prev = h;
            }
            current = head;
        }
    }
    void prepend(int n);
    int get_element(){return current->d;}
    void advance(){current = current->next;}
    void print();

    ~list()
    {
        for(current = head; current != nullptr;)
        {
            current = head->next;
            delete head;
            head = current;
        }
    }

};

list::list(const int* arr, int n) : head(nullptr), current(nullptr)
{
    for(int i = 0; i < n; ++i)
    {
        prepend(arr[i]);
    }
}

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
    int data[10] = {3, 4, 6, 7, -3, 5};
    list d(data, 6);
    list e(data, 10);
    a.prepend(9); a.prepend(8);
    cout << " list a " << endl;

    for(int i = 0; i < 40; ++i) b.prepend(i*i);
    cout << " list b" << endl;
    b.print();
    list c(b);
    c.print();
    d.print();
    e.print();

    return 0;
}