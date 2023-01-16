#include "Testing.h"

Testing::Testing(std::string url, int count) : TestsGenerator(url, count) {
    filesURL = url;
    filesCount = count;
}

void Testing::StartTests() {
    for (int i = 1; i <= filesCount; i++) {
        VanEmdeBoasTree* vanEmdeBoasTree;

        std::string urlIn = filesURL + std::to_string(i) + ".in";
        std::string urlOut = filesURL + std::to_string(i) + ".out";
        std::string urlAns = filesURL + std::to_string(i) + ".ans";

        std::ifstream fin(urlIn);

        if(!fin.is_open()) {
            std::cout << "Не удалось открыть файл: " << i << ".in" << "\n";
        }
        else {
            std::ifstream ans(urlAns);
            std::ofstream fout(urlOut);

            std::string word;
            std::string wordSub;
            fin >> word;

            auto b = std::chrono::steady_clock::now();

            vanEmdeBoasTree = new VanEmdeBoasTree(std::stoi(word));

            auto e = std::chrono::steady_clock::now();
            auto el_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(e - b);

            fout << "Create - " << el_ms << "\n";

            while(true) {
                fin >> word;
                if (word == "e") break;

                if(word == findSymbol) {
                    fin >> word;
                    ans >> wordSub;

                    auto begin = std::chrono::steady_clock::now();

                    bool answer = vanEmdeBoasTree->Find(stoi(word));

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << answer << (std::to_string(answer) == wordSub ? " OK " : " Error ")
                    << "Find - " << elapsed_ms << "\n";
                }
                else if(word == insertSymbol) {
                    fin >> word;

                    auto begin = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->Insert(stoi(word));

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << "Insert - " << elapsed_ms << "\n";
                }
                else if(word == removeSymbol) {
                    fin >> word;

                    auto begin = std::chrono::steady_clock::now();

                    vanEmdeBoasTree->RemoveVEB(stoi(word));

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << "Remove - " << elapsed_ms << "\n";
                }
                else if(word == successorSymbol) {
                    fin >> word;
                    ans >> wordSub;

                    auto begin = std::chrono::steady_clock::now();

                    int answer = vanEmdeBoasTree->SuccessorVEB(stoi(word));

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << answer << (answer == std::stoi(wordSub) ? " OK " : " Error ")
                    << "SuccessorVEB - " << elapsed_ms << "\n";
                }
                else if(word == predecessorSymbol) {
                    fin >> word;
                    ans >> wordSub;

                    auto begin = std::chrono::steady_clock::now();

                    int answer = vanEmdeBoasTree->PredecessorVEB(stoi(word));

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                    fout << answer << (answer == std::stoi(wordSub) ? " OK " : " Error ")
                    << "PredecessorVEB - " << elapsed_ms << "\n";
                }
                else if(word == maximumSymbol) {
                    ans >> wordSub;
                    int answer = vanEmdeBoasTree->MaximumVEB();
                    fout << answer << (answer == std::stoi(wordSub) ? " OK" : " Error") << "\n";
                }
                else if(word == minimumSymbol) {
                    ans >> wordSub;
                    int answer = vanEmdeBoasTree->MinimumVEB();
                    fout << answer << (answer == std::stoi(wordSub) ? " OK" : " Error") << "\n";
                }
            }

            ans.close();
            fout.close();
        }
        fin.close();
    }
}

void Testing::GenerateTests() {
    TestsGenerator::GenerateTests();
}

