#include <iostream>

#include "SearchEngine.h"

int main(int argc, char** argv) {

    using namespace std;

    SearchEngine searchEngine(argv[2]);
    searchEngine.parseDatabase(argv[2]);
    searchEngine.search(argv[1]);

    return 0;
}
