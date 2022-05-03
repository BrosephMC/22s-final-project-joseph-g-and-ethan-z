#include <iostream>
#include <string>

#include "SearchEngine.h"
#include "DSHashTable.h"

using namespace std;

int main(int argc, char** argv) {

    SearchEngine sE(argv[1]);
    sE.start();

    return 0;
}
