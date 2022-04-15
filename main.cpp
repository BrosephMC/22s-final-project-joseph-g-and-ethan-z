#include <iostream>

#include "DocumentParser.h"

#include <dirent.h>

int main(int argc, char** argv) {

    using namespace std;

    cout << "Hello, World!" << endl;

    cout << argv[1] << endl;

    DocumentParser document;
    //document.ParseDocument("temporary_data/blogs_0000001.json");
    //document.ParseDocument("C:/Users/jojog/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a/blogs_0000001.json");
    //document.ParseDocument("/mnt/c/Users/jojog/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a/blogs_0000001.json");
    document.ParseDocument(argv[1]);

    document.ParseText(document.returnString("text").c_str());

    //https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
    DIR *dir; struct dirent *diread;
    vector<char *> folders;

    char* path = "/mnt/c/Users/jojog/Downloads/archive";

    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            folders.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return EXIT_FAILURE;
    }

    cout << " List of folders:" << endl;
    for (auto folder : folders) cout << folder << "| ";
    cout << endl << endl;

    for (auto folder : folders){
        cout << "w1" << endl;
        cout << folder << " < this is a folder" << endl;
        cout << "w2" << endl;
        vector<char *> files;

        cout << "w3" << endl;
        char *appendedPath;
        cout << "w4" << endl;
        strcpy(appendedPath, path);
        strcat(appendedPath, "/");
        strcat(appendedPath, folder);
        cout << appendedPath << endl;

        cout << "w5";
        if ((dir = opendir(appendedPath)) != nullptr) {
            cout << "w6";
            while ((diread = readdir(dir)) != nullptr) {
                files.push_back(diread->d_name);
            }
            closedir (dir);
        } else {
            cout << "could not open dir of appended path" << endl;
            perror ("opendir");
            return EXIT_FAILURE;
        }

        for (auto file : files) cout << file << "| ";
        cout << endl;
    }

    //for (auto file : files) cout << file << "| ";
    //cout << endl;
    //

    return 0;
    //DocumentParser.parsedocuments(asdfsadf);
}
