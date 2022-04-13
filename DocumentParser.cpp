//
// Created by jojog on 4/11/2022.
//

#include "DocumentParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void DocumentParser::ParseDocument(char *file) {
    int maxCharCount = 10000;
    char wholeFile[maxCharCount];

    fstream data_file;
    data_file.open(file);
    data_file.getline(wholeFile, maxCharCount);
    data_file.close();
    cout << wholeFile << endl;

    doc.Parse(wholeFile);
}

void DocumentParser::ParseText(const char *text) {

    istringstream ss(text);
    string word;

    while (ss >> word){
        cout << word << endl;
        //insert into AVL tree
    }
}

string DocumentParser::returnString(char *index) {
    cout << doc[index].GetString() << endl;
    return doc[index].GetString();
}

void DocumentParser::test() {
    cout << doc["entities"]["persons"]["name"].GetString() << endl;

    doc.ParseInsitu("text");
}
