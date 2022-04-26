//
// Created by jojog on 4/11/2022.
//

#include "QueryProcessor.h"
#include "DocumentParser.h"

//stem the user query
void QueryProcessor::Search(string query, IndexHandler &ih) {

    istringstream ss(query);
    string word;
    vector<string> queryList;
    DocumentParser doc;

    //insert words into queryList vector
    while(ss >> word){
        if(word != "AND" && word != "OR" && word != "NOT" && word != "ORG" && word != "PERSON"){
            doc.simplifyWord(word);
        }
        queryList.push_back(word);
    }

    cout << queryList.size() << endl;

    for(int i = 0; i < queryList.size(); i++) {
        cout << "SEARCH" << endl;
        word = queryList.at(i);

        cout << "search word: " << word << endl;

        if(word == "AND"){
            //AND element1 element2
            cout << "AND" << endl;
            string word1 = queryList.at(i+1);
            string word2 = queryList.at(i+2);
            if(ih.containsWord(word1) && ih.containsWord(word2)){
                cout << "has both words" << endl;
                getIntersection(ih.getWord(word1).articles, ih.getWord(word2).articles);
            } else {
                cout << "does not have both words" << endl;
            }
            i+= 2;
            continue;
        } else if(word == "NOT"){
            cout << "NOT implementation needed" << endl;
        }

        //if single word
        if (ih.containsWord(word)) {
            WordData element = ih.getWord(word);
            cout << element.articles.size() << endl;
            for (int i = 0; i < element.articles.size(); i++) {
                cout << element.articles.at(i) << endl;
            }
            cout << endl;
        } else {
            cout << "Word not found" << endl;
        }

        cout << "SEARCH end" << endl;
    }

}

//https://www.youtube.com/watch?v=ZkvWJlSAaSA
void QueryProcessor::getIntersection(vector<string> vector1, vector<string> vector2){

    vector<string> intersection;

    cout << "Intersection: " << endl;

    for(int i = 0; i < vector1.size(); i++){
        int j;
        for(j = 0; j < i; j++){
            if(vector1.at(i) == vector1.at(j)){
                break;
            }
        }
        if(j == i){
            intersection.push_back(vector1.at(i));
        }
    }

    for(int i = 0; i < intersection.size(); i++){
        bool hasIntersection = false;
        for(int j = 0; j < vector2.size(); j++){
            if(intersection.at(i) == vector2.at(j)){
                hasIntersection = true;
            }
        }
        if(hasIntersection){
            cout << " - " << intersection.at(i) << endl;
        }
    }
}

//std union intersection library
//PERSON and ORG search will always be AND
