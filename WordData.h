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
    std::vector<std::string> filePaths;
    std::vector<std::string> dates;

    //Constructors and Destructors
    WordData(const std::string& w) { word = w; }

    //Overloaded Operators
    //Checks if the two WordDatas contain the same data
    bool operator== (const WordData& otherWord) const { return word == otherWord.word; }
    //Checks if word equals the inputted string
    bool operator== (const std::string& otherString) const { return word == otherString; }
    //Checks if this WordData is less than another
    bool operator< (const WordData& otherWord) const { return word < otherWord.word; }
    //Checks if word is less than the inputted string
    bool operator< (const std::string& otherString) const { return word < otherString; }
    //Checks if this WordData is less than or equal to another
    bool operator<= (const WordData& otherWord) const { return word <= otherWord.word; }
    //Checks if word is less than or equal to the inputted string
    bool operator<= (const std::string& otherString) const { return word <= otherString; }

    friend std::ostream& operator<< (std::ostream& output, const WordData& wordData)
    {
        output << wordData.word << std::endl;

        for(const std::string& a : wordData.articles){
            output << a << " ";
        }
        output << std::endl;

        for(const std::string& f : wordData.filePaths){
            output << f << " ";
        }
        output << std::endl;

        for(const std::string& d : wordData.dates){
            output << d << " ";
        }
        output << std::endl;

    }
};

#endif //INC_22S_FINAL_PROJ_WORDDATA_H
