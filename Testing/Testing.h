#ifndef VAN_EMDEBOAS_TREE_TESTING_H
#define VAN_EMDEBOAS_TREE_TESTING_H

#include <string>
#include <fstream>
#include <iostream>
#include "../vEB Tree/VanEmdeBoasTree.h"

class Testing {

private:
    int filesCount;
    std::string filesURL;

    const std::string findSymbol = "f";
    const std::string insertSymbol = "i";
    const std::string removeSymbol = "r";
    const std::string successorSymbol = "s";
    const std::string predecessorSymbol = "p";
    const std::string maximumSymbol = "u";
    const std::string minimumSymbol = "d";

public:
    Testing(std::string URL, int count);

    void StartTests();
};


#endif //VAN_EMDEBOAS_TREE_TESTING_H
