#include <iostream>

#include "DocumentParser.h"

int main() {

    using namespace std;

    cout << "Hello, World!" << endl;

    DocumentParser document;
    document.ParseDocument("temporary_data/blogs_0000001.json");
    //document.ParseDocument("C:/Users/jojog/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a/blogs_0000001.json");

    document.ParseText(document.returnString("text").c_str());

    return 0;
    //DocumentParser.parsedocuments(asdfsadf);
}
