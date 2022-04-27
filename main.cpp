#include <iostream>

#include "SearchEngine.h"

int main(int argc, char** argv) {

    using namespace std;

    SearchEngine searchEngine;
    searchEngine.parseDatabase(argv[2]);
    string input;
    while(input != "q"){
        cout << "Search query (type \"q\" to quit): " << endl;
        getline(cin, input);
        if(input == "q")
            break;
        searchEngine.search(input);
    }

    return 0;
}
