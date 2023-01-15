#include "VanEmdeBoasTree.h"

int VanEmdeBoasTree::High(int x) const
{
    int div = ceil(sqrt(universeSize));
    return x / div;
}

int VanEmdeBoasTree::Low(int x) const
{
    int mod = ceil(sqrt(universeSize));
    return x % mod;
}

int VanEmdeBoasTree::GenerateIndex(int x, int y) const
{
    int ru = ceil(sqrt(universeSize));
    return x * ru + y;
}


VanEmdeBoasTree::VanEmdeBoasTree(int size) {
    universeSize = size;
    minimum = -1;
    maximum = -1;

    if(size <= 2) {
        summary = nullptr;
        clusters = new VanEmdeBoasTree*[0];
    }
    else {
        int sizeOfNewClusters = ceil(sqrt(size));

        summary = new VanEmdeBoasTree(sizeOfNewClusters);

        clusters = new VanEmdeBoasTree*[sizeOfNewClusters];

        for (int i = 0; i < sizeOfNewClusters; ++i) {
            clusters[i] = new VanEmdeBoasTree(ceil(sqrt(size)));
        }
    }
}

VanEmdeBoasTree::~VanEmdeBoasTree() {
    delete summary;
    delete[] clusters;
}

int VanEmdeBoasTree::MinimumVEB() const {
    return minimum;
}

int VanEmdeBoasTree::MaximumVEB() const {
    return maximum;
}

void VanEmdeBoasTree::Insert(int key) {
    if(minimum == -1) {
        minimum = key;
        maximum = key;
    }
    else {
        if(key < minimum)
            std::swap(key, minimum);

        if(universeSize > 2) {
            if(clusters[High(key)]->MinimumVEB() == -1) {
                summary->Insert(High(key));
                clusters[High(key)]->minimum = Low(key);
                clusters[High(key)]->maximum = Low(key);
            }
            else {
                clusters[High(key)]->Insert(Low(key));
            }
        }

        if (key > maximum) {
            maximum = key;
        }
    }
}

int VanEmdeBoasTree::SuccessorVEB(int key) {
    if(universeSize == 2) {
        if(key == 0 && maximum == 1)
            return 1;
        else
            return -1;
    }
    else if (minimum != -1 && key < minimum){
        return minimum;
    }
    else {
        int maxElementInCluster = clusters[High(key)]->MaximumVEB();
        int offset, successorCluster;

        if (maxElementInCluster != -1 && Low(key) < maxElementInCluster) {
            offset = clusters[High(key)]->SuccessorVEB(Low(key));
            return GenerateIndex(High(key), offset);
        }

        else {
            successorCluster = summary->SuccessorVEB(High(key));

            if (successorCluster == -1) {
                return -1;
            }
            else {
                offset = clusters[successorCluster]->MinimumVEB();
                return GenerateIndex(successorCluster, offset);
            }
        }
    }
}

int VanEmdeBoasTree::PredecessorVEB(int key) {
    if (universeSize == 2) {
        if (key == 1 && minimum == 0)
            return 0;
        else
            return -1;
    }
    else if (maximum != -1 && key > maximum) {

        return maximum;
    }
    else {
        int minInCluster = clusters[High(key)]->MinimumVEB();
        int offset{ 0 }, pred_cluster{ 0 };

        if (minInCluster != -1 && Low(key) > minInCluster) {
            offset = clusters[High(key)]->PredecessorVEB(Low(key));

            return GenerateIndex(High(key), offset);
        }
        else {
            pred_cluster = summary->PredecessorVEB(High(key));

            if (pred_cluster == -1) {
                if (minimum != -1 && key > minimum) {
                    return minimum;
                } else
                    return -1;
            }
            else {
                offset = clusters[pred_cluster]->MaximumVEB();

                return GenerateIndex(pred_cluster, offset);
            }
        }
    }
}

void VanEmdeBoasTree::RemoveVEB(int key) {
    if(!Find(key)) return;
    if (maximum == minimum) {
        minimum = -1;
        maximum = -1;
    }
    else if (universeSize == 2) {
        if (key == 0) {
            minimum = 1;
        }
        else {
            minimum = 0;
        }
        maximum = minimum;
    }
    else {
        if (key == minimum) {
            int first_cluster = summary->MinimumVEB();

            key = GenerateIndex(first_cluster, clusters[first_cluster]->MinimumVEB());
            minimum = key;
        }

        clusters[High(key)]->RemoveVEB(Low(key));

        if (clusters[High(key)]->MinimumVEB() == -1) {
            summary->RemoveVEB(High(key));

            if (key == maximum) {
                int maxInSummary = summary->MaximumVEB();

                if (maxInSummary == -1) {
                    maximum = minimum;
                }
                else {
                    maximum = GenerateIndex(maxInSummary, clusters[maxInSummary]->MaximumVEB());
                }
            }
        }
        else if (key == maximum) {
            maximum = GenerateIndex(High(key), clusters[High(key)]->MaximumVEB());
        }
    }
}

bool VanEmdeBoasTree::Find(int key) {
    if (universeSize < key) {
        return false;
    }
    if (minimum == key || maximum == key) {
        return true;
    }
    else {
        if (universeSize == 2) {
            return false;
        }
        else {
            return clusters[High(key)]->Find(Low(key));
        }
    }
}

void VanEmdeBoasTree::PrintTreeAfterKey(int key) {
    if(SuccessorVEB(key) == -1) return;
    int newKey = SuccessorVEB(key);
    std::cout << newKey << " ";
    PrintTreeAfterKey(newKey);
}