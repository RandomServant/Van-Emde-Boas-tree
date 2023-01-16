#ifndef VAN_EMDEBOAS_TREE_TESTING_H
#define VAN_EMDEBOAS_TREE_TESTING_H

#include "TestsGenerator.h"

class Testing : TestsGenerator {

public:;
    Testing(std::string URL, int count);

    void StartTests();
    void GenerateTests();
};


#endif //VAN_EMDEBOAS_TREE_TESTING_H
