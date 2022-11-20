#include "Testing/Testing.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Testing *test = new Testing("Tests/", 2);
    test->StartTests();
    return 0;
}


