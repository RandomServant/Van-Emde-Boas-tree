#include "TestsGenerator.h"

TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::GenerateTests() {
    std::random_device rand;
    std::mt19937 gen(rand());

    k = 2;

    for (int i = 1; i <= filesCount; i++) {
        std::string urlIn = filesURL + std::to_string(i) + ".in";
        std::string urlOut = filesURL + std::to_string(i) + ".out";
        std::string urlAns = filesURL + std::to_string(i) + ".ans";

        std::ofstream fin(urlIn);
        std::ofstream fout(urlOut);
        std::ofstream fans(urlAns);

        universeSize = int(pow(2, k));
        std::uniform_int_distribution<> dist(0, universeSize - 1);

        fin << universeSize << "\n";

        fin << "i " << 0 << "\n";
        fin << "i " << universeSize - 1 << "\n";

        fin << "s " << 0 << "\n";
        fans << universeSize - 1 <<"\n";

        fin << "p " << universeSize - 1 << "\n";
        fans << 0 <<"\n";

        for (int j = 1; j < universeSize - 1; j++) {
            fin << "i " << j << "\n";
        }

        fin << "f " << dist(gen) << "\n";
        fans << 1 <<"\n";

        fin << "r " << dist(gen) << "\ne";

        k++;

        fin.close();
        fout.close();
        fans.close();
    }
}