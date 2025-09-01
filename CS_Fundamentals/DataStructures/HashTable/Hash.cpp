#include <iostream>
#include <stdlib.h>
#include "Hash.h"

using std::cout; using std::endl;


Hash::Hash(size_t size) {
    tableSize = size;
    hashTable = new int[tableSize];
    occupied = new bool[tableSize]();
}


Hash::~Hash() {
    delete[] hashTable;
    delete[] occupied;
}


size_t Hash::hashFunction(const int& key) {
    return static_cast<size_t>(key) % tableSize; 
}


void Hash::insert(const int& value) {
    size_t idx = hashFunction(value);
    hashTable[idx] = value;
    occupied[idx] = true;
}


bool Hash::containsKey(const int& value) {
    size_t idx = hashFunction(value);
    if (hashTable[idx] == value) return true; 
    else return false;
}


int* Hash::search(const int& value) {
    size_t idx = hashFunction(value);
    if (hashTable[idx] == value) return &hashTable[idx];
    else return nullptr;
}


void Hash::remove(const int& value) {
    size_t idx = hashFunction(value);
    if (occupied[idx]) occupied[idx] = false;
}


void Hash::deleteTable() {
    delete[] hashTable;
    delete[] occupied;
    hashTable = nullptr;
    occupied = nullptr;
    tableSize = 0;
}


void Hash::printTable(){
    for (size_t i = 0; i < tableSize; i++) {
        if (occupied[i]) cout << i << ": " << hashTable[i] << endl;
    }
}