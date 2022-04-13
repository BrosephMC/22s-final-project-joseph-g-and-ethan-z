//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJ_WORDDATA_H
#define INC_22S_FINAL_PROJ_WORDDATA_H

#include <string>
#include <vector>

struct WordData{
public:
    //Indexed word
    std::string word;
    //Articles that contain the word
    std::vector<std::string> articles;

    //Constructors and Destructors
    WordData(const std::string& w) { word = w; }

    //Overloaded Operators
    //Checks if the two WordDatas contain the same data
    bool operator== (const WordData&) const;
    //Checks if word equals the inputted string
    bool operator== (const std::string&) const;
};

#endif //INC_22S_FINAL_PROJ_WORDDATA_H
