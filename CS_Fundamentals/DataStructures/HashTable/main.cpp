#include <iostream>
#include "Hash.h"

int main() {

    Hash* hash = new Hash();

    hash->insert(10);
    hash->insert(2001);
    hash->printTable();

    delete hash;

    return 0;
}