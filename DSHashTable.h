//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJ_DSHASHTABLE_H
#define INC_22S_FINAL_PROJ_DSHASHTABLE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <list>

#include "WordData.h"

class DSHashTable{
private:
    list<WordData>* table;
    int currentElements = 0;
    int maxElements;

    void resize();

public:
    DSHashTable(int size);

    void insert(const WordData& element);

    WordData& operator[](const std::string& key);

    WordData& operator[](const WordData& key);
};

void DSHashTable::resize() {
    int newMax = maxElements * maxElements;
    list<WordData>* newTable = new list<WordData>[newMax];

    std::hash<std::string> hasher;
    for(int i = 0; i < maxElements; i++){
        for(WordData& x : table[i]){
            int location = hasher(x.word) % newMax;
            newTable[location].push_back(x);
        }
    }

    maxElements = newMax;
    delete[] table;
    table = newTable;
}

DSHashTable::DSHashTable(int size) {
    maxElements = size;
    table = new list<WordData>[maxElements];
}

void DSHashTable::insert(const WordData& element) {
    std::hash<std::string> hasher;
    auto location = hasher(element.word) % maxElements;
    cout << "Inserted " << element << " at " << location << endl;
    table[location].push_back(element);
    currentElements++;

    if(currentElements > maxElements)
        resize();
}

WordData &DSHashTable::operator[](const string& key) {
    try{
        std::hash<std::string> hasher;
        int location = hasher(key) % maxElements;
        for(WordData& x : table[location]){
            if(x == key)
                return x;
        }
        throw std::runtime_error("DSHashTable[]: Search element not in table.");
    }catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

WordData &DSHashTable::operator[](const WordData& key) {
    try{
        std::hash<std::string> hasher;
        int location = hasher(key.word);
        cout << "Got here" << endl;
        for(WordData& x : table[location]){
            if(x == key)
                return x;
        }
        throw std::runtime_error("DSHashTable[]: Search element not in table.");
    }catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
}


#endif //INC_22S_FINAL_PROJ_DSHASHTABLE_H
