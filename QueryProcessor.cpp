//
// Created by jojog on 4/11/2022.
//

#include "QueryProcessor.h"
#include "DocumentParser.h"

//stem the user query
void QueryProcessor::Search(string query, IndexHandler &ih, IndexHandler &ihORG, IndexHandler &ihPERSON) {

    istringstream ss(query);
    string word;
    vector<string> queryList;
    DocumentParser doc;
    vector<string> results;

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

    printResults(results);

}

//https://stackoverflow.com/questions/19483663/vector-intersection-in-c
vector<string> QueryProcessor::intersection(vector<string> &v1, vector<string> &v2) {
    vector<string> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

//https://stackoverflow.com/questions/641724/remove-the-common-entities-from-two-vector
vector<string> QueryProcessor::difference(vector<string> &v1, vector<string> &v2) {
    vector<string> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_difference(v1.begin(),v1.end(),
                     v2.begin(),v2.end(),
                     back_inserter(v3));
    return v3;
}

void QueryProcessor::printResults(vector<string> &results) {
    cout << "Final search results: " << endl;
    cout << results.size() << endl;

    //https://thispointer.com/c-how-to-find-duplicates-in-a-vector/

    // Create a map to store the frequency of each element in vector
    map<string, int> countMap;
    // Iterate over the vector and store the frequency of each element in map
    for (auto & elem : results)
    {
        auto loopResult = countMap.insert(pair<string, int>(elem, 1));
        if (loopResult.second == false)
            loopResult.first->second++;
    }

    sortMap(countMap);

    // Iterate over the map
    for (auto & elem : countMap)
    {
        cout << elem.first;
        if(elem.second > 1)
            cout << " x" << elem.second;
        cout << endl;
    }
}

//https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/
bool QueryProcessor::cmpMap(pair<string, int>& a, pair<string, int>& b)
{
    return (a.second < b.second);
}

void QueryProcessor::sortMap(map<string, int>& M)
{

    // Declare vector of pairs
    vector<pair<string, int> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(),QueryProcessor::cmpMap);

    // Print the sorted value
    //for (auto& it : A) {
    //
    //    cout << it.first << ' '
    //         << it.second << endl;
    //}
}
