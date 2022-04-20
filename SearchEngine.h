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
    //IndexHandler ihORG;
    //IndexHandler ihPERSON;
    QueryProcessor q;

public:
    //Constructors and Destructors
    SearchEngine(const string& dataBase);

    void parseDatabase(char*& path);

    /**
     * Returns the articles which best fit the entered query.
     * TODO: Figure out a return type
     * @param query - Entered search terms.
     */
    void search(const std::string& query);
};

#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_SEARCHENGINE_H
