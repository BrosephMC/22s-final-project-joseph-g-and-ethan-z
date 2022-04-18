#include <iostream>

#include "DocumentParser.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"

int main(int argc, char** argv) {

    using namespace std;

    cout << "Hello, World!" << endl;

    cout << argv[1] << endl;

    DocumentParser document;
    IndexHandler ih;
    QueryProcessor q;

    //document.ParseDocument("/mnt/c/Users/jojog/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a/news_0034753.json");
    //document.ParseText(document.returnString("text").c_str());

    document.ParseDatabase(argv[1], ih);

    q.Search("time", ih);

    return 0;
}
