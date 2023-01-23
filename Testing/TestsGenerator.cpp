#include "TestsGenerator.h"

TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::StartGeneratingAndTesting(std::string function) {
    VanEmdeBoasTree* veb;

    std::string urlOut = filesURL + function + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        veb = new VanEmdeBoasTree(universeSize);

        if (function == insertSymbol) {
            auto begin = std::chrono::steady_clock::now();

            for (int j = 0; j < testCount; j++) {
                veb->Insert(j % universeSize);
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                              / testCount;
            fout << elapsed_ns.count() << "\n";

            delete veb;
            continue;
        }
        else if (function == removeSymbol) {
            auto begin = std::chrono::steady_clock::now();

            for (int j = 0; j < testCount; j++) {
                veb->RemoveVEB(j % universeSize);
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                              / testCount;
            fout << elapsed_ns.count() << "\n";

            delete veb;
            continue;
        }

        for (int j = 0; j < universeSize; j++) {
            veb->Insert(j);
        }

        if (function == findSymbol) {
            auto begin = std::chrono::steady_clock::now();

            for (int j = 0; j < testCount; j++) {
                veb->Find(j % universeSize);
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                    / testCount;
            fout << elapsed_ns.count() << "\n";
        }
        else if (function == successorSymbol) {
            auto begin = std::chrono::steady_clock::now();

            for (int j = 0; j < testCount; j++) {
                veb->SuccessorVEB(j % universeSize);
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                              / testCount;
            fout << elapsed_ns.count() << "\n";
        }
        else if (function == predecessorSymbol) {
            auto begin = std::chrono::steady_clock::now();

            for (int j = 0; j < testCount; j++) {
                veb->PredecessorVEB(j % universeSize);
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                              / testCount;
            fout << elapsed_ns.count() << "\n";
        }

        delete veb;
    }
    fout.close();
}


