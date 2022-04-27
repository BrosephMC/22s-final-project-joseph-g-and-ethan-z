//
// Created by jojog on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H

#include <string>
#include "IndexHandler.h"
#include "porter2_stemmer.h"
#include <map>;

using namespace std;

class QueryProcessor {

public:

    void Search(string word, IndexHandler &ih, IndexHandler &ihORG, IndexHandler &ihPERSON);
    void printResults(vector<string> &results);
    vector<string> intersection(vector<string> &v1, vector<string> &v2);
    vector<string> difference(vector<string> &v1, vector<string> &v2);
    void sortMap(map<string, int>& M);
    static bool cmpMap(pair<string, int>& a, pair<string, int>& b);

};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
