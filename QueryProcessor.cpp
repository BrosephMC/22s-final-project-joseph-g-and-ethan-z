//
// Created by jojog on 4/11/2022.
//

#include "QueryProcessor.h"
#include "DocumentParser.h"
#include <chrono>
#include "WordData.h"

//stem the user query
void QueryProcessor::Search(string query, IndexHandler &ih, IndexHandler &ihORG, IndexHandler &ihPERSON) {

    istringstream ss(query);
    string word;
    vector<string> queryList;
    DocumentParser doc;
    vector<WordData::Article> results;

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::duration<double> time_in_seconds;
    start = chrono::high_resolution_clock::now();

    //insert words into queryList vector
    while(ss >> word){
        if(word != "AND" && word != "OR" && word != "NOT" && word != "ORG" && word != "PERSON"){
            doc.simplifyWord(word);
        }
        queryList.push_back(word);
        if(word == "ORG" || word == "PERSON"){
            ss >> word;
            queryList.push_back(word);
        }
    }

    //iterate through each word
    for(int i = 0; i < queryList.size(); i++) {
        cout << " SEARCH" << endl;
        word = queryList.at(i);
        cout << "search word: " << word << endl;

        if(word == "OR"){
            continue;
        }
        else if(word == "AND"){
            //AND element1 element2
            cout << "AND" << endl;
            try {
                string word1 = queryList.at(i + 1);
                string word2 = queryList.at(i + 2);
                if (ih.containsWord(word1) && ih.containsWord(word2)) {
                    cout << "has both words: " << word1 << " and " << word2 << endl;
                    results = intersection(ih.getWord(word1).articles, ih.getWord(word2).articles);
                } else {
                    cout << "does not have both words" << word1 << " and " << word2 << endl;
                }
                i += 2;
                continue;
            } catch(const std::exception& e) {
                cout << "Insufficient arguments" << endl;
                i+= 100;
                continue;
            }
        }
        else if(word == "NOT"){
            cout << "NOT" << endl;
            try {
                string word1 = queryList.at(i + 1);
                if (ih.containsWord(word1)) {
                    cout << "has NOT word: " << word1 << endl;
                    int differenceNum = results.size();
                    results = difference(results, ih.getWord(word1).articles);
                    cout << "overlap: " << labs(differenceNum - results.size()) << endl;
                } else {
                    cout << "does not have NOT word: " << word1 << endl;
                }
                i += 1;
                continue;
            } catch(const std::exception& e) {
                cout << "Insufficient arguments" << endl;
                i += 100;
                continue;
            }
        }
        else if(word == "ORG"){
            cout << "ORG" << endl;
            string word1 = queryList.at(i+1);
            cout << word1 << endl;
            if(ihORG.containsWord(word1)){
                results = intersection(ihORG.getWord(word1).articles, results);
            } else {
                cout << "does not have ORG: " << word1 << endl;
                results = {};
            }
            i+=1;
            continue;
        }
        else if(word == "PERSON"){
            cout << "PERSON" << endl;
            string word1 = queryList.at(i+1);
            cout << word1 << endl;
            if(ihPERSON.containsWord(word1)){
                results = intersection(ihPERSON.getWord(word1).articles, results);
            } else {
                cout << "does not have PERSON: " << word1 << endl;
                results = {};
            }
            i+=1;
            continue;
        }

        //if single word
        if (ih.containsWord(word)) {
            WordData element = ih.getWord(word);
            cout << element.articles.size() << endl;
            for (int i = 0; i < element.articles.size(); i++) {
                cout << element.articles.at(i) << endl;
                results.push_back(element.articles.at(i));
            }
            cout << endl;
        } else {
            cout << "Word not found" << endl;
        }

        cout << "SEARCH end" << endl;
    }

    //output stats
    displayGeneralStats(ih);
    cout << "Search Statistics" << endl;
    cout << " You searched: " << query << endl;

    end = chrono::high_resolution_clock::now();
    time_in_seconds = end - start;
    cout << fixed << " Search time in seconds: " << time_in_seconds.count() << endl;

    //prints results
    printResults(results);

}

//https://stackoverflow.com/questions/19483663/vector-intersection-in-c
template <typename T>
vector<T> QueryProcessor::intersection(vector<T> &v1, vector<T> &v2) {
    vector<T> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

//https://stackoverflow.com/questions/641724/remove-the-common-entities-from-two-vector
template <typename T>
vector<T> QueryProcessor::difference(vector<T> &v1, vector<T> &v2) {
    vector<T> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_difference(v1.begin(),v1.end(),
                     v2.begin(),v2.end(),
                     back_inserter(v3));
    return v3;
}

void QueryProcessor::printResults(vector<WordData::Article> &results) {
    cout << " Total number of articles found (including duplicates): " << results.size() << endl;
    cout << "--Search results--" << endl << endl;

    //https://thispointer.com/c-how-to-find-duplicates-in-a-vector/

    // Create a map to store the frequency of each element in vector
    map<WordData::Article, int> countMap;

    // Iterate over the vector and store the frequency of each element in map
    for (auto & elem : results)
    {
        auto loopResult = countMap.insert(pair<WordData::Article, int>(elem, 1));
        if (loopResult.second == false)
            loopResult.first->second++;
    }

    vector<pair<int, WordData::Article>> invertedPair;

    //make the count map inverted so it can sort by number
    for (auto const &pair: countMap) {
        invertedPair.emplace_back(pair.second, pair.first);
    }

    sort(invertedPair.begin(),invertedPair.end());

    //display results
    int count = 15;
    int limit = invertedPair.size()-count;
    if(limit < 0){
        count += limit;
        limit = 0;
    }
    for (int i = invertedPair.size()-1; i >= limit; i--) {
        pair < int, WordData::Article> elem = invertedPair.at(i);
        cout << "Article #" << invertedPair.size()-i << endl;
        DocumentParser dp;
        dp.displayFileData(elem.second.filePath);
        cout << " File path: " << elem.second.filePath << endl;
        if(elem.first > 1)
            cout << " Word occurrences: " << "x" << elem.first << endl;
        cout << endl;
    }

    //user query loop - search, page, or open
    string input;
    int pageNumber = 1;
    while(input != "s"){
        cout << endl;
        cout << "Type s to search again" << endl;
        cout << "Type p to turn to the next page of articles" << endl;
        cout << "Type o to open an article" << endl;
        getline(cin, input);

        if(input == "s"){
            break;
        }
        else if(input == "p"){
            if(count < 15){
                cout << "cannot turn page" << endl;
            } else {
                limit -= 15;
                if(limit < 0){
                    count += limit;
                    limit = 0;
                }
                pageNumber += 1;
                //
                cout << "asdf " << invertedPair.size() << endl;
                cout << " Total number of articles found (including duplicates): " << results.size() << endl;
                cout << "--Search results page: " << pageNumber << "--" << endl << endl;
                for (int i = invertedPair.size()-1-((pageNumber-1)*15); i >= limit; i--) {
                    pair < int, WordData::Article> elem = invertedPair.at(i);
                    cout << "Article #" << invertedPair.size()-i << endl;
                    DocumentParser dp;
                    dp.displayFileData(elem.second.filePath);
                    cout << " File path: " << elem.second.filePath << endl;
                    if(elem.first > 1)
                        cout << " Word occurrences: " << "x" << elem.first << endl;
                    cout << endl;
                }
                //
            }
        }
        else if(input == "o"){
            cout << "Type in an article number " << (pageNumber-1)*15+1 << "-" << (pageNumber-1)*15 + count << ": " << endl;
            getline(cin, input);
            bool invalid = false;
            for(int i = 0; i < input.length(); i++){
                if(!isdigit(input[i])){
                    invalid = true;
                    continue;
                }
            }
            if(!invalid){
                if(stoi(input) >= (pageNumber-1)*15+1 && stoi(input) <= (pageNumber-1)*15 + count){
                    DocumentParser dp;
                    dp.openArticle(invertedPair.at(invertedPair.size()-stoi(input)).second.filePath);
                } else {
                    cout << "not a valid article number" << endl;
                }
            } else {
                cout << "not a valid article number" << endl;
            }

        }
    }
}

void QueryProcessor::displayGeneralStats(IndexHandler &ih) {
    cout << endl << "General Statistics" << endl;
    cout << " Total number of words indexed: " << ih.getNodeCount() << endl;
    //top 25 most frequent words
    //total number of unique orgs and persons entities
    //total number of articles parsed
}
