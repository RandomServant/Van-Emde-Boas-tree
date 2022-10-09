#include <iostream>
#include <vector>

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
};

int main() {
    Van_Emde_Boas_Tree* veb = new Van_Emde_Boas_Tree(1);
}
