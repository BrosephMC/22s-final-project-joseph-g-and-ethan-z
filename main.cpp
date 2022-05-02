#include <iostream>
#include <string>

#include "SearchEngine.h"
#include "DSHashTable.h"

using namespace std;

int main(int argc, char** argv) {

    DSHashTable table(2);
    WordData hello("hello");
    hello.articles.push_back("534850");
    hello.articles.push_back("489537");
    WordData goodbye("goodbye");
    goodbye.articles.push_back("549388");
    WordData how("how");
    how.articles.push_back("875439");

    table.insert(hello);
    table.insert(goodbye);
    table.insert(how);

    cout << table["goodbye"].articles[0] << endl;
    table["goodbye"].articles[0] = "000000";
    cout << table["goodbye"].articles[0] << endl;

    string input;
    SearchEngine searchEngine;
    searchEngine.parseDatabase(argv[2]);
     do {
        cout << "Search query: " << endl;
        getline(cin, input);
         if(input == "q")
             break;
        cout << "cin: " << input << endl;
        searchEngine.search(input);
    } while(input != "q");

    return 0;
}
