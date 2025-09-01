#ifndef HASH_H
#define HASH_H

class Hash {
    private:
        size_t tableSize;
        int* hashTable;
        bool* occupied;

        size_t hashFunction(const int& key);
    public:
        Hash(size_t size = 101);
        ~Hash();

        void insert(const int& value);
        int* search(const int& value);
        bool containsKey(const int& value);
        void remove(const int& value);
        void deleteTable();
        void printTable();
};

#endif