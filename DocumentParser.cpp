//
// Created by jojog on 4/11/2022.
//

#include "DocumentParser.h"
#include <iostream>
#include <fstream>

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

    doc.Parse(text);
    //cout << doc["Hours"].GetString() << endl;
}

string DocumentParser::returnString(char *index) {
    cout << doc[index].GetString() << endl;
    return doc[index].GetString();
}

vector<string> DocumentParser::returnStringVector(char *index1, char *index2) {
    vector<string> vector;
    for(auto &current : doc[index1][index2].GetArray()) {
        std::cout << "value: " << current.GetString() << std::endl;
        //vector.push_back(current.GetString());
        vector.emplace_back(current.GetString());
    }
    return vector;
}

void DocumentParser::test() {
    cout << doc["entities"]["persons"]["name"].GetString() << endl;

    doc.ParseInsitu("text");
}
