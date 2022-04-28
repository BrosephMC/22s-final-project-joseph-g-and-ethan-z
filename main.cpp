#include <iostream>
#include <string>

#include "SearchEngine.h"
#include "DSHashTable.h"

using namespace std;

int main(int argc, char** argv) {

    DSHashTable table(50);
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

    cout << table["hello"].articles[0] << endl;
    table["hello"].articles[0] = "000000";
    cout << table["hello"].articles[0] << endl;


    return 0;
}
