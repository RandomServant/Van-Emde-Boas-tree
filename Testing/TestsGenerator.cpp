#include "TestsGenerator.h"

TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::GenerateTests(std::string function) {
    std::random_device rand;
    std::mt19937 gen(rand());

    for (int i = 1; i <= filesCount; i++) {
        std::string urlIn = filesURL +
                (function != insertSymbol && function != removeSymbol ? function : insertSymbol + removeSymbol) +
                std::to_string(i) + ".in";
        std::string urlOut = filesURL +
                (function != insertSymbol && function != removeSymbol ? function : insertSymbol + removeSymbol) +
                std::to_string(i) + ".out";

        std::ofstream fin(urlIn);
        std::ofstream fout(urlOut);

        universeSize = int(pow(2, i + 1));
        std::uniform_int_distribution<> dist(0, universeSize - 1);

        if (function == "c") {
            for (int j = 0; j < testCount; j++) {
                fin << universeSize << "\n";
            }

            fin << "e";

            fin.close();
            fout.close();

            continue;
        }

        fin << universeSize << "\n";

        if (function == "i" || function == "r") {
            for (int j = 0; j < testCount; ) {
                for (int k = 0; k < universeSize; k++) {
                    fin << insertSymbol + " "<< k << "\n";
                }
                for (int k = 0; k < universeSize; k++) {
                    fin << removeSymbol + " "<< k << "\n";
                }
                j += universeSize;
            }

            fin << "e";

            fin.close();
            fout.close();

            continue;
        }

        fin << "i " << 0 << "\n";
        fin << "i " << universeSize - 1 << "\n";

        if (function == successorSymbol) {
            for (int j = 0; j < testCount; j++) {
                fin << successorSymbol + " " << 0 << "\n";
            }

            fin << "e";

            fin.close();
            fout.close();

            continue;
        }
        if (function == predecessorSymbol) {
            for (int j = 0; j < testCount; j++) {
                fin << predecessorSymbol + " " << universeSize - 1 << "\n";
            }

            fin << "e";

            fin.close();
            fout.close();

            continue;
        }

        for (int j = 1; j < universeSize - 1; j++) {
            fin << insertSymbol + " " << j << "\n";
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                fin << findSymbol + " " << dist(gen) << "\n";
            }

            fin << "e";

            fin.close();
            fout.close();

            continue;
        }
    }
}

void TestsGenerator::StartTests(std::string function) {
    for (int i = 1; i <= filesCount; i++) {
        VanEmdeBoasTree* vanEmdeBoasTree;

        std::string urlIn = filesURL +
                (function != insertSymbol && function != removeSymbol ? function : insertSymbol + removeSymbol) +
                std::to_string(i) + ".in";
        std::string urlOut = filesURL +
                (function != insertSymbol && function != removeSymbol ? function : insertSymbol + removeSymbol) +
                std::to_string(i) + ".out";

        std::ifstream fin(urlIn);
        std::ofstream fout(urlOut);

        std::string word;

        if (function == "c") {
            while (true) {
                fin >> word;

                if (word == "e") break;

                auto b = std::chrono::steady_clock::now();

                vanEmdeBoasTree = new VanEmdeBoasTree(std::stoi(word));

                auto e = std::chrono::steady_clock::now();
                auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                fout << el_ms << "\n";

                delete vanEmdeBoasTree;
            }
            fin.close();
            fout.close();

            continue;
        }

        fin >> word;

        vanEmdeBoasTree = new VanEmdeBoasTree(std::stoi(word));

        if (function == findSymbol ||
            function == successorSymbol ||
            function == predecessorSymbol) {
            while (true) {
                fin >> word;

                if (word == "e") break;

                if(word == findSymbol) {
                    fin >> word;

                    auto b = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->Find(std::stoi(word));

                    auto e = std::chrono::steady_clock::now();
                    auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                    fout << el_ms << "\n";
                }
                else if(word == successorSymbol) {
                    fin >> word;

                    auto b = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->SuccessorVEB(std::stoi(word));

                    auto e = std::chrono::steady_clock::now();
                    auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                    fout << el_ms << "\n";
                }
                else if(word == successorSymbol) {
                    fin >> word;

                    auto b = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->PredecessorVEB(std::stoi(word));

                    auto e = std::chrono::steady_clock::now();
                    auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                    fout << el_ms << "\n";
                }
            }
        }
        else if (function == insertSymbol || function == removeSymbol) {
            while (true) {
                fin >> word;

                if (word == "e") break;

                if (word == insertSymbol) {
                    fin >> word;

                    auto b = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->Insert(std::stoi(word));

                    auto e = std::chrono::steady_clock::now();
                    auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                    fout << el_ms << "\n";
                }
                else if (word == removeSymbol) {
                    fin >> word;

                    auto b = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->RemoveVEB(std::stoi(word));

                    auto e = std::chrono::steady_clock::now();
                    auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

                    fout << el_ms << "\n";
                }
            }
        }
        fin.close();
        fout.close();
    }
}
