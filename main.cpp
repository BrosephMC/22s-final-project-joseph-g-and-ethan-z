#include <iostream>

#include "DocumentParser.h"

int main() {

    using namespace std;

    cout << "Hello, World!" << endl;

    DocumentParser document;
    document.ParseDocument("temporary_data/blogs_0000001.json");

    document.ParseText(document.returnString("text").c_str());

    return 0;
    //DocumentParser.parsedocuments(asdfsadf);
}
