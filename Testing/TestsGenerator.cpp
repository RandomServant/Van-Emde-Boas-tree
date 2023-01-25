#include "TestsGenerator.h"


TestsGenerator::TestsGenerator(std::string URL, int count)
{
	filesURL = URL;
	filesCount = count;
}

void TestsGenerator::StartGeneratingAndTestingVEB(std::string function, bool random) {
    VanEmdeBoasTree* veb;

    std::string urlOut = filesURL + "veb_" + (function != insertSymbol && function != removeSymbol ?
            function : insertSymbol + removeSymbol) + (random ? "_r" : "") + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        int *arr = new int[universeSize];

        std::string urlArray = filesURL + "Arrays/array" + std::to_string(i + 2) + ".txt";
        std::ifstream farray(urlArray);

        if (farray.fail()) {
            std::ofstream farr(urlArray);
            arr = FisherYatesShuffle::GenerateArray(universeSize, random);

            for (int j = 0; j < universeSize; j++) {
                farr << arr[j] << " ";
            }
        }
        else {
            for (int j = 0; j < universeSize; ++j) {
                farray >> arr[j];
            }
        }

        veb = new VanEmdeBoasTree(universeSize);

        if (function == insertSymbol || function == removeSymbol) {
            for (int j = 0; j < testCount;) {
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    veb->Insert(arr[k]);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    veb->RemoveVEB(arr[k]);

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
            veb->Insert(arr[j]);
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->Find(arr[j % universeSize]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == successorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->SuccessorVEB(arr[j % (universeSize - 1)]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == predecessorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                veb->PredecessorVEB(arr[(j % (universeSize - 1)) + 1]);

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

void TestsGenerator::StartGeneratingAndTestingSET(std::string function, bool random) {
    std::set<int> orderSet;

    std::string urlOut = filesURL + "os_" + (function != insertSymbol && function != removeSymbol ?
            function : insertSymbol + removeSymbol) + (random ? "_r" : "") + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        int *arr = new int[universeSize];

        std::string urlArray = filesURL + "Arrays/array" + std::to_string(i + 2) + ".txt";
        std::ifstream farray(urlArray);

        if (farray.fail()) {
            std::ofstream farr(urlArray);
            arr = FisherYatesShuffle::GenerateArray(universeSize, random);

            for (int j = 0; j < universeSize; j++) {
                farr << arr[j] << " ";
            }
        }
        else {
            for (int j = 0; j < universeSize; ++j) {
                farray >> arr[j];
            }
        }

        if (function == insertSymbol || function == removeSymbol) {
            for (int j = 0; j < testCount;) {
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    orderSet.insert(arr[k]);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    orderSet.erase(arr[k]);

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
            orderSet.insert(arr[j]);
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.find(arr[j % universeSize]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == successorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.upper_bound(arr[j % (universeSize - 1)]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
        else if (function == predecessorSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                orderSet.lower_bound(arr[(j % (universeSize - 1)) + 1]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
    }
    fout.close();
}

void TestsGenerator::StartGeneratingAndTestingUNSET(std::string function, bool random) {
    std::unordered_set<int> unOrderSet;

    std::string urlOut = filesURL + "us_" + (function != insertSymbol && function != removeSymbol ?
            function : insertSymbol + removeSymbol) + (random ? "_r" : "") + ".time";

    std::ofstream fout(urlOut);

    for (int i = 0; i < filesCount; i++) {
        universeSize = int(pow(2, i + 2));

        int *arr = new int[universeSize];

        std::string urlArray = filesURL + "Arrays/array" + std::to_string(i + 2) + ".txt";
        std::ifstream farray(urlArray);

        if (farray.fail()) {
            std::ofstream farr(urlArray);
            arr = FisherYatesShuffle::GenerateArray(universeSize, random);

            for (int j = 0; j < universeSize; j++) {
                farr << arr[j] << " ";
            }
        }
        else {
            for (int j = 0; j < universeSize; ++j) {
                farray >> arr[j];
            }
        }

        if (function == insertSymbol || function == removeSymbol) {
            for (int j = 0; j < testCount;) {
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    unOrderSet.insert(arr[k]);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                for (int k = 0; k < universeSize; k++) {
                    auto begin = std::chrono::steady_clock::now();

                    unOrderSet.erase(arr[k]);

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << elapsed_ns.count() << " ";
                }
                j += universeSize;
            }
            fout << "\n";

            continue;
        }

        unOrderSet.reserve(universeSize);

        for (int j = 0; j < universeSize; j++) {
            unOrderSet.insert(arr[j]);
        }

        if (function == findSymbol) {
            for (int j = 0; j < testCount; j++) {
                auto begin = std::chrono::steady_clock::now();

                unOrderSet.find(arr[j % universeSize]);

                auto end = std::chrono::steady_clock::now();
                auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                fout << elapsed_ns.count() << " ";
            }
            fout << "\n";
        }
    }
    fout.close();
}



