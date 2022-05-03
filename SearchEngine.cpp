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
            document.ParseDatabase(dataBasePath, ih, ihORG, ihPERSON);
            cout << "Completed" << endl;
        }
        else if(input == "3")
            ih.saveIndex();
        else if(input == "4")
            ih.loadIndex();
    }
}

SearchEngine::SearchEngine(char*& dataBase){
    dataBasePath = dataBase;
}

void SearchEngine::parseDatabase() {
    document.ParseDatabase(dataBasePath, ih, ihORG, ihPERSON);
}

void SearchEngine::search(const string& query) {
    q.Search(query, ih, ihORG, ihPERSON);
}
