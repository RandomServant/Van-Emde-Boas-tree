#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Van_Emde_Boas_Tree {
    
public:
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
};

int main() {
    ifstream fin("Tests\\01.txt");
    Van_Emde_Boas_Tree* veb = new Van_Emde_Boas_Tree(1);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << " - ";
    char a[50];
    fin.getline(a, 50);
    cout << a << endl;
    veb->Insert(4);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << " - ";
    veb->Insert(6);
    cout << veb->minimumVEB() << " " << veb->maximumVEB() << " - ";
    fin.close();
    return 0;
}
