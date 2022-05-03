//
// Owner - Ethan Zech
//

#include "IndexHandler.h"
#include <fstream>

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

//
void IndexHandler::addNodeCount(int num) {
    nodeCount += num;
}

int IndexHandler::getNodeCount() {
    return nodeCount;
}

void IndexHandler::saveIndex() {
    std::ofstream output("IndexProfile.dat");
    wordIndex.outputPreOrder(output);
    output.close();
}
//
