#ifndef VAN_EMDEBOAS_TREE_TESTING_H
#define VAN_EMDEBOAS_TREE_TESTING_H

#include "TestsGenerator.h"

class Testing : TestsGenerator {

public:;
    Testing(std::string URL, int count);

    void StartTesting();
    void StartGeneratingAndTesting(std::string function) override;
};


#endif //VAN_EMDEBOAS_TREE_TESTING_H
