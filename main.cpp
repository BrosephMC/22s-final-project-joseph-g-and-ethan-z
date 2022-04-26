#include <iostream>

#include "SearchEngine.h"

int main(int argc, char** argv) {

    using namespace std;

    SearchEngine searchEngine;
    searchEngine.parseDatabase(argv[2]);
    string input;
    cout << "Search query: " << endl;
    getline(cin, input);
    searchEngine.search(input);

    return 0;
}
