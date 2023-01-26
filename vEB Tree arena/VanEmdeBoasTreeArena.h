/*
#ifndef CHART_PY_VANEMDEBOASTREEARENA_H
#define CHART_PY_VANEMDEBOASTREEARENA_H

#include <iostream>
#include <vector>

class VanEmdeBoasTreeArena {

private:
    unsigned int universeSize;
    unsigned int minimum;
    unsigned int maximum;

    unsigned int High(int x) const;
    unsigned int Low(int x) const;
    unsigned int GenerateIndex(int x, int y) const;
    static unsigned int sqrtVEB(unsigned int x) ;

    void SizeOfSummaries(unsigned int& sizeOfSummaries, unsigned int universeSize);

public:
    VanEmdeBoasTreeArena(unsigned int size);
    std::vector<bool> elements;

    ~VanEmdeBoasTreeArena();

    unsigned int MinimumVEB() const;
    unsigned int MaximumVEB() const;

    void Insert(int key);
    unsigned int SuccessorVEB(int key);
    unsigned int PredecessorVEB(int key);
    void RemoveVEB(int key);
    bool Find(int key);
};


#endif //CHART_PY_VANEMDEBOASTREEARENA_H
*/
