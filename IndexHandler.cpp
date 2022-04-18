//
// Owner - Ethan Zech
//

#include "IndexHandler.h"
#include <fstream>

void IndexHandler::insertWord(const std::string& word) {
    wordIndex.insert(WordData(word));
}

void IndexHandler::indexWord(const std::string& word, const std::string& articleID) {
    if(!wordIndex.contains(word)){
        insertWord(word);
    }
    else{
        WordData* searchWord = &getWord(WordData(word));
        searchWord->articles.push_back(articleID);
    }
}

bool IndexHandler::containsWord(const WordData& word) const {
    return wordIndex.contains(word);
}

WordData &IndexHandler::getWord(const WordData& word) {
    return wordIndex.find(word);
}
