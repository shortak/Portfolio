#include <iostream>
#include "LinkedLists.h"

int main() {
    SList* slist = new SList;
    slist -> placeFront(50);
    slist -> placeFront(33);
    slist -> placeFront(40);
    std::cout << "Test List:" << std::endl;
    slist -> printList();

    std::cout << "Place 60 at the end of list: "  << std::endl;
    slist -> placeBack(60);
    slist -> printList();

    std::cout << "Insert node after 3rd index: " << std::endl;
    slist -> insertNode(3, 100);
    slist -> printList();

    std::cout << "Insert node before 3rd index: " << std::endl;
    slist -> insertNode(3, 101, "before_idx");
    slist -> printList();
    
    std::cout << "Delete element 50 from list: " << std::endl;
    slist -> deleteNode(50);
    slist -> printList();

    std::cout << "Return value from 3rd Node from last node:" << std::endl;
    slist -> findKthFromEnd(3);


    std::cout << "Reverse list" << std::endl;
    slist -> reverseList();
    slist -> printList();

    delete slist;
    return 0;
}

