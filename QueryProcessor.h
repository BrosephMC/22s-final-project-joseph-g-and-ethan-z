//
// Created by jojog on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H

#include <string>
#include "IndexHandler.h"
#include "porter2_stemmer.h"

using namespace std;

class QueryProcessor {

public:

    void Search(string word, IndexHandler &ih);

};


#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_QUERYPROCESSOR_H
