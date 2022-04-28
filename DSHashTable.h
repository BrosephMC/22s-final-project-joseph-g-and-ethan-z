//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJ_DSHASHTABLE_H
#define INC_22S_FINAL_PROJ_DSHASHTABLE_H

#include <iostream>
#include <string>
#include <functional>
#include <list>

#include "WordData.h"

class DSHashTable{
private:
    list<WordData>* table;
    int totalElements;

public:
    DSHashTable(int size);

    void insert(const WordData& element);

    WordData& operator[](const std::string& key);

    WordData& operator[](const WordData& key);
};

DSHashTable::DSHashTable(int size) {
    totalElements = size;
    table = new list<WordData>[totalElements];
}

void DSHashTable::insert(const WordData& element) {
    std::hash<std::string> hasher;
    auto location = hasher(element.word) % totalElements;
    cout << "Inserted " << element << " at " << location << endl;
    table[location].push_back(element);
}

WordData &DSHashTable::operator[](const string& key) {
    std::hash<std::string> hasher;
    int location = hasher(key) % totalElements;
    for(WordData& x : table[location]){
        if(x == key)
            return x;
    }
}

WordData &DSHashTable::operator[](const WordData& key) {
    std::hash<std::string> hasher;
    int location = hasher(key.word);
    cout << "Got here" << endl;
    for(WordData& x : table[location]){
        if(x == key)
            return x;
    }
}


#endif //INC_22S_FINAL_PROJ_DSHASHTABLE_H
