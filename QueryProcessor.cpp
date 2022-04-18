//
// Created by jojog on 4/11/2022.
//

#include "QueryProcessor.h"

//stem the user query
void QueryProcessor::Search(string word, IndexHandler &ih) {
    std::cout << "SEARCH" << std::endl;
    Porter2Stemmer::stem(word);
    WordData element = ih.getWord(word);
    cout << element.articles.size() << endl;
    for(int i = 0; i < element.articles.size(); i++){
        cout << element.articles.at(i);
    }
    cout << endl;
    std::cout << "SEARCH end" << std::endl;
}
