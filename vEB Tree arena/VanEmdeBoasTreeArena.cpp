/*
#include "VanEmdeBoasTreeArena.h"

unsigned int VanEmdeBoasTreeArena::sqrtVEB(unsigned int x) {
    return ceil(sqrt(x));
}

unsigned int VanEmdeBoasTreeArena::High(int x) const
{
    int div = ceil(sqrt(universeSize));
    return x / div;
}

unsigned int VanEmdeBoasTreeArena::Low(int x) const
{
    int mod = ceil(sqrt(universeSize));
    return x % mod;
}

unsigned int VanEmdeBoasTreeArena::GenerateIndex(int x, int y) const
{
    int ru = ceil(sqrt(universeSize));
    return x * ru + y;
}

int null = -1;

VanEmdeBoasTreeArena::VanEmdeBoasTreeArena(unsigned int size) {
    universeSize = size;
    minimum = null;
    maximum = null;

    unsigned int generalSize = size;
    unsigned int sizeOfSummaries = 0;

    SizeOfSummaries(sizeOfSummaries, size);

    elements.resize(generalSize + sizeOfSummaries);
}

void VanEmdeBoasTreeArena::SizeOfSummaries(unsigned int &sizeOfSummaries, unsigned int universeSize) {
    if(universeSize <= 2) return;

    universeSize = sqrtVEB(universeSize);
    sizeOfSummaries += universeSize;

    SizeOfSummaries(sizeOfSummaries,  universeSize);

    for (int i = 0; i < universeSize; ++i) {
        SizeOfSummaries(sizeOfSummaries, universeSize);
    }
}

VanEmdeBoasTreeArena::~VanEmdeBoasTreeArena() {

}

unsigned int VanEmdeBoasTreeArena::MinimumVEB() const {
    return minimum;
}

unsigned int VanEmdeBoasTreeArena::MaximumVEB() const {
    return maximum;
}

void VanEmdeBoasTreeArena::Insert(int key) {
    elements[key] = true;

    if (minimum == null) {
        minimum = key;
        maximum = key;
    }
    else {
        if (key < minimum)
            minimum = key;



        if (key > maximum)
            maximum = key;
    }
}

unsigned int VanEmdeBoasTreeArena::SuccessorVEB(int key) {
    return null;
}

unsigned int VanEmdeBoasTreeArena::PredecessorVEB(int key) {
    return null;
}

void VanEmdeBoasTreeArena::RemoveVEB(int key) {

}

bool VanEmdeBoasTreeArena::Find(int key) {
    if (elements[key])
        return true;
    return false;
}


*/
