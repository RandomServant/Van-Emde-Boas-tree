#include "TestsGenerator.h"

TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::StartGeneratingAndTestingVEB(std::string function) {
    VanEmdeBoasTree* veb;

    std::string urlOut = filesURL + "veb_" + (function != insertSymbol && function != removeSymbol ?
            function : insertSymbol + removeSymbol) + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        veb = new VanEmdeBoasTree(universeSize);

        if (function == insertSymbol || function == removeSymbol) {
            for (int j = 0; j < testCount;) {
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    veb->Insert(k);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    veb->RemoveVEB(k);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                j += universeSize;
            }
            fout << "\n";

            delete veb;
            continue;
        }

        for (int j = 0; j < universeSize; j++) {
            veb->Insert(j);
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->Find(j % universeSize);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == successorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->SuccessorVEB(j % (universeSize - 1));

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == predecessorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->PredecessorVEB((j % (universeSize - 1)) + 1);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }

        delete veb;
    }
    fout.close();
}

void TestsGenerator::StartGeneratingAndTestingSET(std::string function) {
    std::set<int> orderSet;

    std::string urlOut = filesURL + "os_" + (function != insertSymbol && function != removeSymbol ?
            function : insertSymbol + removeSymbol) + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        if (function == insertSymbol || function == removeSymbol) {
            for (int j = 0; j < testCount;) {
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    orderSet.insert(k);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                   orderSet.erase(k);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                j += universeSize;
            }
            fout << "\n";

            continue;
        }

        for (int j = 0; j < universeSize; j++) {
            orderSet.insert(j);
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.find(j % universeSize);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == successorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.upper_bound(j % (universeSize - 1));

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == predecessorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.lower_bound((j % (universeSize - 1)) + 1);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
    }
    fout.close();
}


