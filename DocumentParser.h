//
// Created by jojog on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H

#include "include/rapidjson/document.h"
#include <string>
#include <vector>

using namespace std;

class DocumentParser {

public:
    rapidjson::Document doc;

    void ParseDocument(char* file);
    void ParseText(const char *text);
    string returnString(char* index);
    vector<string> returnStringVector(char* index1, char* index2);

    void test();

    //breakup text into words
    //remove stop words
    //stem words
    //parse multiple files

    //get list of orgs
    //get list of persons

};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H
