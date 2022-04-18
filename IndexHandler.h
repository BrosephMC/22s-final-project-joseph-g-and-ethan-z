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
     * Returns if the given word corresponds to any WordData in the wordIndex.
     * @param word - Word to check for.
     * @return Whether the word is in the tree or not.
     */
    bool containsWord(const WordData& word) const;

    /**
     * Returns a reference to the WordData that corresponds with the entered word. Throws an error if
     * the word isn't in the tree; call containsWord first.
     * @param word - Word to return.
     * @return WordData that corresponds with the entered word.
     */
    WordData& getWord(const WordData& word);
};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_INDEXHANDLER_H
