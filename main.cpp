#include <iostream>
#include <string>

#include "SearchEngine.h"
#include "DSHashTable.h"

using namespace std;

int main(int argc, char** argv) {

    SearchEngine sE(argv[1]);
    //sE.start();

    string input;
    sE.parseDatabase();
     do {
        cout << "Search query (type q to quit): " << endl;
        getline(cin, input);
         if(input == "q")
             break;
        cout << "cin: " << input << endl;
        sE.search(input);
    } while(input != "q");

    return 0;
}
