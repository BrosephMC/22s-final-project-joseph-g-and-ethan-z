//
// Created by jojog on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H

#include "include/rapidjson/document.h"
#include <string>
#include <vector>
#include <map>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "porter2_stemmer.h"

using namespace std;

class DocumentParser {

public:
    rapidjson::Document doc;

    map<string, string> stopWords;

    //Initializer
    DocumentParser();

    /**
     * Prepares the specified document for parsing with RapidJson
     * @param file - file path
     */
    void ParseDocument(char* file);

    /**
     * Splits corresponding text field of json element into words
     * @param index - string json element
     */
    void ParseText(const char *text);

    /**
     * Returns corresponding text field of json element with RapidJson
     * @param index - string json element
     */
    string returnString(char* index);

    /**
     * Parses a set of files
     * @param path - file path to folder
     */
    void ParseDatabase(char * path);

    /**
     * Converts word to lower case, removes extra characters, and stems word
     * @param text - string to modify
     */
    void simplifyWord(string& text);

    //get list of orgs
    //get list of persons

};

//stopword map/hashmap/hashtable


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DOCUMENTPARSER_H
