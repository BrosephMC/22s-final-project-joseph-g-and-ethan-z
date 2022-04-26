//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_SEARCHENGINE_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_SEARCHENGINE_H

#include "DocumentParser.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"
#include <string>

class SearchEngine {
private:
    string dataBasePath = "";

    DocumentParser document;
    IndexHandler ih;
    IndexHandler ihORG;
    IndexHandler ihPERSON;
    QueryProcessor q;

public:
    //Constructors and Destructors
    //SearchEngine(const string& dataBase);
    SearchEngine();

    /**
     * Calls the ParseDatabse function in DocumentParser
     * @param path - set of folders to parse
     */
    void parseDatabase(char*& path);

    /**
     * Returns the articles which best fit the entered query.
     * TODO: Figure out a return type
     * @param query - Entered search terms.
     */
    void search(const std::string& query);

    //User Interface
    //  allows the user to clear the index completely
    //  allows the user to manage the persistent index (see Index Persistence .. for more info)
    //  allows the user to parse a document dataset to populate the index OR read from the persistence file
    //  allow the user to enter a Boolean query (as described ..).

    //Article Output
    //  title
    //  publication
    //  date published
    //  complete text of article
    //  Total number of individual articles indexed
    //  The total number of unique words indexed (total nodes in the word AVL Tree)
    //  EC: use std::chrono to time how long it takes to execute the complete query
    //  EC: Total number of unique Orgs and Person entities.
    //  EC: Top 25 most frequent words in descending order  (NOT including stopwords)
};

#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_SEARCHENGINE_H
