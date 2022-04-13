//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_INDEXHANDLER_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_INDEXHANDLER_H

#include "DSAVLTree.h"
#include "WordData.h"
#include <string>

class IndexHandler {
private:
    DSAVLTree<WordData> wordIndex;

public:
    /**
     * Adds the given word to the word index.
     * @param word - Word to be added to the index.
     */
    void insertWord(const std::string& word);

    /**
     * Inserts the word if it isn't already in the index then adds the articleID to that word.
     * @param word - Word to find or create in the index.
     * @param articleID - ID of the article the word was found in.
     */
    void indexWord(const std::string& word, const std::string& articleID);

    /**
     * Returns a reference to the WordData that corresponds with the entered word.
     * @param word - Word to return.
     * @return WordData that corresponds with the entered word.
     */
    WordData& getWord(const std::string& word);
};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_INDEXHANDLER_H
