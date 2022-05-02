//
// Created by jojog on 4/11/2022.
//

#include "SearchEngine.h"

using namespace std;

/*
SearchEngine::SearchEngine(const string &dataBase) : dataBasePath(dataBase) {

}
 */

void SearchEngine::start() {
    string input("");
    while(input != "5"){
        cout << "S E A R C H   E N G I N E" << endl;
        cout << "=========================" << endl;
        cout << "1) Search" << endl;
        cout << "2) Create Index" << endl;
        cout << "3) Save Current Index" << endl;
        cout << "4) Load Current Index" << endl;
        cout << "5) Quit" << endl;
        cout << endl;
        cout << "Select an option: "; cin >> input;
        cout << endl;

        if(input == "1"){
            string query("");
            cout << "Enter a query: "; cin >> query;
            cout << endl;
            search(query);
        }
        else if(input == "2"){
            char* filePath("");
            cout << "Enter the file path to parse: "; cin >> filePath;
            cout << endl;
            document.ParseDatabase(filePath, ih, ihORG, ihPERSON);
            cout << "Completed" << endl;
        }
    }
}

SearchEngine::SearchEngine(){}

void SearchEngine::parseDatabase(char*& path) {
    document.ParseDatabase(path, ih, ihORG, ihPERSON);
}

void SearchEngine::search(const string& query) {
    q.Search(query, ih, ihORG, ihPERSON);
}
