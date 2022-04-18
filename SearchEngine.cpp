//
// Created by jojog on 4/11/2022.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine(const string &dataBase) : dataBasePath(dataBase) {

}

void SearchEngine::parseDatabase(char*& path) {
    document.ParseDatabase(path, ih);
}

void SearchEngine::search(const string& query) {
    q.Search(query, ih);
}
