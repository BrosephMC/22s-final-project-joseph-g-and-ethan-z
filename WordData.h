//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJ_WORDDATA_H
#define INC_22S_FINAL_PROJ_WORDDATA_H

#include <string>
#include <vector>

struct WordData{
public:
    struct Article{
    public:
        std::string article;
        std::string filePath;
        std::string date;

        Article(const std::string& art, const std::string& file, const std::string& dt){
            article = art; filePath = file; date = dt;
        }

        //Stub
        bool operator< (const Article otherArticle) const {
            if(this->article < otherArticle.article){
                return true;
            } else {
                return false;
            }
        }
        friend std::ostream& operator<< (std::ostream& output, const Article& thisArticle){
            output << thisArticle.article << std::endl << thisArticle.filePath << std::endl
                << thisArticle.date << std::endl;
        }
    };

    //Indexed word
    std::string word;
    //Articles that contain the word
    std::vector<Article> articles;

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

    void insertArticle(const std::string& art, const std::string& file, const std::string& date){
        articles.push_back(Article(art, file, date));
    }

    friend std::ostream& operator<< (std::ostream& output, const WordData& wordData)
    {
        output << wordData.word << std::endl;

        output << "-" << std::endl;
        for(const Article& a : wordData.articles){
            output << a;
        }
        output << "-" << std::endl;

    }
};

#endif //INC_22S_FINAL_PROJ_WORDDATA_H
