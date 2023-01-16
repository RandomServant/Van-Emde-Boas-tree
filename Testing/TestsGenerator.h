#ifndef VAN_EMDEBOAS_TREE_TESTSGENERATOR_H
#define VAN_EMDEBOAS_TREE_TESTSGENERATOR_H

#include "../vEB Tree/VanEmdeBoasTree.h"
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>

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

    TestsGenerator(std::string URL, int count);

    void GenerateTests();

private:
    int k, universeSize, buffer;
};

#endif //VAN_EMDEBOAS_TREE_TESTSGENERATOR_H
