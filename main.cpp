#include <iostream>
#include <fstream>

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

int main() {

    using namespace std;

    cout << "Hello, World!" << endl;

    int maxCharCount = 10000;
    char wholeFile[maxCharCount];

    fstream data_file;
    data_file.open("temporary_data/blogs_0000001.json");
    data_file.getline(wholeFile, maxCharCount);
    data_file.close();
    cout << wholeFile << endl;

    rapidjson::Document doc;
    doc.Parse(wholeFile);
    cout << doc["uuid"].GetString() << endl;

    // 1. Parse a JSON string into DOM.
    //const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    //rapidjson::Document doc;
    //doc.Parse(json);

    // 2. Modify it by DOM.
    //rapidjson::Value& s = doc["stars"];
    //s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    //rapidjson::StringBuffer buffer;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    //doc.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    //std::cout << buffer.GetString() << std::endl;
    //cout << doc["project"].GetString() << endl;

    return 0;
    //DocumentParser.parsedocuments(asdfsadf);
}
