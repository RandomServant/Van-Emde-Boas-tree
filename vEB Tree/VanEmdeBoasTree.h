/*
    Этот заголовочный файл содержит библиотеку с++ с реализацией алгоритма "Дерево ван Эмде Боасса"

    Подключение:
    #include "VanEmdeBoasTree.h"

    Создание дерева ван Эмде Боаса и выделение памяти N:
    VanEmdeBoasTree *название = new VanEmdeBoasTree(N);

    Операция вставки:
    название->Insert(x);

    Операция удаления:
    название->Remove(x);

    Операция поиска:
    название->Find(x);

    Операция преемника:
    название->SuccessorVEB(x);

    Операция предшественника:
    название->PredecessorVEB(x);
*/

#ifndef VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H
#define VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H

#include <iostream>

class VanEmdeBoasTree {

private:
    int universeSize;
    int minimum;
    int maximum;
    VanEmdeBoasTree* summary;
    VanEmdeBoasTree** clusters;

    int High(int x) const;
    int Low(int x) const;
    int GenerateIndex(int x, int y) const;


public:
    VanEmdeBoasTree(int size);

    ~VanEmdeBoasTree();

    int MinimumVEB() const;
    int MaximumVEB() const;

    void Insert(int key);
    int SuccessorVEB(int key);
    int PredecessorVEB(int key);
    void RemoveVEB(int key);
    bool Find(int key);
};


#endif //VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H
