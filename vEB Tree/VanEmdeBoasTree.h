#include <iostream>
#include <vector>

#ifndef VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H
#define VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H

class VanEmdeBoasTree {

private:
    int universeSize;
    int minimum;
    int maximum;
    VanEmdeBoasTree* summary;
    std::vector<VanEmdeBoasTree*> clusters;

    int High(int x) const;
    int Low(int x) const;
    int GenerateIndex(int x, int y) const;


public:
    VanEmdeBoasTree(int size);

    ~VanEmdeBoasTree();

    int minimumVEB() const;
    int maximumVEB() const;

    void Insert(int key);
    int SuccessorVEB(int key);
    int PredecessorVEB(int key);
    void RemoveVEB(int key);
    bool Find(int key);

    void PrintTreeAfterKey(int key = 0);
};


#endif //VAN_EMDEBOAS_TREE_VANEMDEBOASTREE_H
