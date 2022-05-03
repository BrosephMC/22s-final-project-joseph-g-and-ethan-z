#include <iostream>
#include <string>

#include "SearchEngine.h"
#include "DSHashTable.h"

using namespace std;

int main(int argc, char** argv) {

    SearchEngine sE(argv[1]);
    sE.start();

//    cout << argv[2] << endl;
//
//    string input;
//    SearchEngine searchEngine;
//    searchEngine.parseDatabase(argv[2]);
//     do {
//        cout << "Search query: " << endl;
//        getline(cin, input);
//         if(input == "q")
//             break;
//        cout << "cin: " << input << endl;
//        searchEngine.search(input);
//    } while(input != "q");

    return 0;
}
