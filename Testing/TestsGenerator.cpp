#include "TestsGenerator.h"

TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::GenerateTests()
{
    for (int i = 1; i <= filesCount; i++) {

        std::string urlIn = filesURL + std::to_string(i) + ".in";
        std::string urlOut = filesURL + std::to_string(i) + ".out";
        std::string urlAns = filesURL + std::to_string(i) + ".ans";

    	std::ofstream fin(urlIn);
        std::ofstream fout(urlOut);
        std::ofstream fans(urlAns);
    }
}

