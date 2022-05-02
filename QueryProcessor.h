//
// Created by jojog on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H

#include <string>
#include "IndexHandler.h"
#include "porter2_stemmer.h"
#include <map>

using namespace std;

class QueryProcessor {

public:

    void Search(string word, IndexHandler &ih, IndexHandler &ihORG, IndexHandler &ihPERSON);
    void printResults(vector<WordData::Article> &results);
    template <typename T>
    vector<T> intersection(vector<T> &v1, vector<T> &v2);
    template <typename T>
    vector<T> difference(vector<T> &v1, vector<T> &v2);
    void openFile(const string& fileName);
    void displayGeneralStats(IndexHandler &ih);

};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
