//
// Owner - Ethan Zech
//

#include "IndexHandler.h"
#include <fstream>

void IndexHandler::indexWord(const std::string& word, const std::string& articleID) {
    wordIndex.indexWordInAVL(word, articleID);
}

bool IndexHandler::containsWord(const WordData& word) const {
    return wordIndex.contains(word);
}

WordData &IndexHandler::getWord(const WordData& word) {
    return wordIndex.find(word);
}
