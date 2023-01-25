#ifndef VAN_EMDEBOAS_TREE_TESTSGENERATOR_H
#define VAN_EMDEBOAS_TREE_TESTSGENERATOR_H

#include "../vEB Tree/VanEmdeBoasTree.h"
#include "../FisherYatesShuffle/FisherYatesShuffle.h"
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include <set>
#include <unordered_set>

class TestsGenerator {

protected:
    int filesCount;
    std::string filesURL;

    const std::string findSymbol = "f";
    const std::string insertSymbol = "i";
    const std::string removeSymbol = "r";
    const std::string successorSymbol = "s";
    const std::string predecessorSymbol = "p";
    const std::string maximumSymbol = "u";
    const std::string minimumSymbol = "d";

    const std::string tagRandom = "r";
    const std::string tagNonRandom = "nr";

    virtual void StartGeneratingAndTestingVEB(std::string function, bool random);
    virtual void StartGeneratingAndTestingSET(std::string function, bool random);
    virtual void StartGeneratingAndTestingUNSET(std::string function, bool random);

    TestsGenerator(std::string URL, int count);

private:
    int universeSize = 0;
    int testCount = 1000000;
};

#endif //VAN_EMDEBOAS_TREE_TESTSGENERATOR_H
