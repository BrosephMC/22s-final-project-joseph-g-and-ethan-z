//
// Owner - Ethan Zech
//

#include "IndexHandler.h"

void IndexHandler::insertWord(const std::string& word) {
    wordIndex.insert(WordData(word));
}

void IndexHandler::indexWord(const std::string& word, const std::string& articleID) {
    if(!wordIndex.contains(word)){
        insertWord(word);
    }

}
