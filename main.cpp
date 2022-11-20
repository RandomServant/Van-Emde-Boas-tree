#include "Testing.h"
#include "VanEmdeBoasTree.h"

using namespace std;

int main() {
    VanEmdeBoasTree* veb = new VanEmdeBoasTree(16);
    cout << sizeof(*veb) << endl;
    veb->PrintTreeAfterKey(0);
    cout << endl;
    veb->RemoveVEB(5);
    veb->PrintTreeAfterKey(0);
    cout << endl;
    veb->Insert(4);
    veb->PrintTreeAfterKey(0);
    cout << endl;
    veb->RemoveVEB(4);
    veb->PrintTreeAfterKey(0);
    cout << endl;
    veb->Insert(3);
    veb->PrintTreeAfterKey(0);
    cout << endl;
    delete veb;
    return 0;
}


