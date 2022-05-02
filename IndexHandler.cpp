//
// Owner - Ethan Zech
//

#include "IndexHandler.h"

void IndexHandler::indexWord(const std::string& word, const std::string& articleID, const std::string& filePath,
                             const std::string& date) {
    wordIndex.indexWordInAVL(word, articleID, filePath, date);
}

bool IndexHandler::containsWord(const WordData& word) const {
    return wordIndex.contains(word);
}

WordData &IndexHandler::getWord(const WordData& word) {
    return wordIndex.find(word);
}
