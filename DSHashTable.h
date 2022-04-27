//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJ_DSHASHTABLE_H
#define INC_22S_FINAL_PROJ_DSHASHTABLE_H

#include <iostream>
#include <list>

//Learned from https://www.educative.io/edpresso/how-to-implement-a-hash-table-in-cpp
//and https://www.journaldev.com/35238/hash-table-in-c-plus-plus
template<typename T>
class DSHashTable{
private:
    list<T>* table;
    int totalElements;

    int getHash(T key);

public:
    DSHashTable(int size);

    void add(T key);

    void remove(T key);
};

template<typename T>
int DSHashTable<T>::getHash(T key) {
    return key % totalElements;
}

template<typename T>
DSHashTable<T>::DSHashTable(int size) {
    totalElements = size;
    table = new list<T>[totalElements];
}

template<typename T>
void DSHashTable<T>::add(T key) {
    table[getHash(key)]
}

#endif //INC_22S_FINAL_PROJ_DSHASHTABLE_H
