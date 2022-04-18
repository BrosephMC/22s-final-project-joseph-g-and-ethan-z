//
// Created by jojog on 4/11/2022.
//

#include "QueryProcessor.h"
#include "DocumentParser.h"

//stem the user query
void QueryProcessor::Search(string word, IndexHandler &ih) {
    std::cout << "SEARCH" << std::endl;
    DocumentParser doc;
    doc.simplifyWord(word);
    cout << "search word: " << word << endl;
    if(ih.containsWord(word)){
        WordData element = ih.getWord(word);
        cout << element.articles.size() << endl;
        for(int i = 0; i < element.articles.size(); i++){
            cout << element.articles.at(i) << endl;
        }
        cout << endl;
    }
    else
        std::cout << "Word not found" << std::endl;
    std::cout << "SEARCH end" << std::endl;
}
