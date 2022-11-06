#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Van_Emde_Boas_Tree {

private:
    int universeSize;
    int minimum;
    int maximum;
    Van_Emde_Boas_Tree* summary;
    vector<Van_Emde_Boas_Tree*> clusters;

    int High(int x)
    {
        int div = ceil(sqrt(universeSize));
        return x / div;
    }

    int Low(int x)
    {
        int mod = ceil(sqrt(universeSize));
        return x % mod;
    }

    int GenerateIndex(int x, int y)
    {
        int ru = ceil(sqrt(universeSize));
        return x * ru + y;
    }


public:
    Van_Emde_Boas_Tree(int size) {
        universeSize = size;
        minimum = -1;
        maximum = -1;

        if(size <= 2) {
            summary = nullptr;
            clusters = vector<Van_Emde_Boas_Tree*>(0);
        }
        else {
            int sizeOfNewClusters = ceil(sqrt(size));

            summary = new Van_Emde_Boas_Tree(sizeOfNewClusters);

            clusters = vector<Van_Emde_Boas_Tree*>(sizeOfNewClusters);

            for (int i = 0; i < sizeOfNewClusters; ++i) {
                clusters[i] = new Van_Emde_Boas_Tree(ceil(sqrt(size)));
            }
        }
    }

    int minimumVEB() {
        return minimum;
    }

    int maximumVEB() {
        return maximum;
    }

    void Insert(int key) {
        if(minimum == -1) {
            minimum = key;
            maximum = key;
        }
        else {
            if(key < minimum)
                swap(key, minimum);

            if(universeSize > 2) {
                if(clusters[High(key)]->minimumVEB() == -1) {
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

    int SuccessorVEB(int key) {
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
            int maxElementInCluster = clusters[High(key)]->maximumVEB();
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
                    offset = clusters[successorCluster]->minimumVEB();
                    return GenerateIndex(successorCluster, offset);
                }
            }
        }
    }

    int PredecessorVEB(int key) {
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
            int minInCluster = clusters[High(key)]->minimumVEB();
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
                    offset = clusters[pred_cluster]->maximumVEB();

                    return GenerateIndex(pred_cluster, offset);
                }
            }
        }
    }

    void RemoveVEB(int key) {
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
                int first_cluster = summary->minimumVEB();

                key = GenerateIndex(first_cluster, clusters[first_cluster]->minimumVEB());
                minimum = key;
            }

            clusters[High(key)]->RemoveVEB(Low(key));

            if (clusters[High(key)]->minimumVEB() == -1) {
                summary->RemoveVEB(High(key));

                if (key == maximum) {
                    int maxInSummary = summary->maximumVEB();

                    if (maxInSummary == -1) {
                        maximum = minimum;
                    }
                    else {
                        maximum = GenerateIndex(maxInSummary, clusters[maxInSummary]->maximumVEB());
                    }
                }
            }
            else if (key == maximum) {
                maximum = GenerateIndex(High(key), clusters[High(key)]->maximumVEB());
            }
        }
    }

    bool Find(int key) {
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
};

int main() {
    Van_Emde_Boas_Tree* veb = new Van_Emde_Boas_Tree(1);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << endl;
    veb->Insert(4);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << endl;
    veb->DeleteVEB(4);
    veb->Insert(6);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << endl;
    veb->Insert(3);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << endl;
    return 0;
}
